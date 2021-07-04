#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT "3490"
#define BACKLOG 10 // 监听队列的长度
// #define BUFSIZE 100

// 进程相关
void sigchld_handler(int s)
{
    // waitpid() might overwrite errno, so we save and restore it:
    int saved_errno = errno;
    // do not block waiting
    while(waitpid(-1, NULL, WNOHANG) > 0);
    errno = saved_errno;
}

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main()
{
    // 服务器回复信息
    char message[] = "Hello, client!";
    // 构建socket地址
    struct addrinfo hints; // 更好地控制返回的套接字地址列表
    struct addrinfo *res; //指向返回地址列表的指针

    socklen_t sin_sz;
    // 存放connector的地址
    char buf[INET6_ADDRSTRLEN];

    // connect的客户端地址
    struct sockaddr_storage connector_addrs;

    // 回收子进程
    struct sigaction sa;
    int child_pid;

    // v1 bug: 在设置后清除了hints
    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // 


    int res_status;
    int listenfd, connetfd;

    
    if ((res_status = getaddrinfo(NULL, PORT, &hints, &res)) != 0) {
        // 出错
        fprintf(stderr, "getaddrinfo: %s", gai_strerror(res_status));
        return 1; // 异常返回
    }

    // 获取文件描述符
    struct addrinfo *p;
    for (p = res; p != NULL; p = p->ai_next) {
        // socket无效
        if ((listenfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("server : socket");
            continue;
        }

        // 处理端口已经被占用的情况
        int yes = 1;
        if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1) {
            perror("setsockopt");
            exit(1);
        }

        // 绑定文件描述符和socket（ip address: port）
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == -1) { // 一次绑定失败
            close(listenfd); // 释放文件描述符
            perror("server : bind");
            continue;
        }

        break; // 绑定成功
    }

    // 释放addrinfo
    freeaddrinfo(res);

    // 是否绑定失败
    if (p == NULL) {
        perror("binding failed.");
        // return 1;
        exit(1); // 退出整个程序
    }

    int listen_status;
    // listen（告诉内核当前的文件描述符是被服务器使用的（默认是客户端））
    if ((listen_status = listen(listenfd, BACKLOG)) == -1) {
        perror("listen failed.");
        exit(1);
    }

    // 回收僵尸进程
    sa.sa_handler = sigchld_handler; // reap all dead processes
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("server: waiting for connections...\n");
    // accept（阻塞，等待客户端请求）
    while (1) {
        sin_sz = sizeof connector_addrs;
        connetfd = accept(listenfd, (struct sockaddr*)&connector_addrs, &sin_sz);
        printf("connect: %d\n", connetfd);
        if (connetfd == -1) {
            perror("accept");
            continue;
        }
        // 将二进制地址转换对应的IPV4/6地址
        inet_ntop(connector_addrs.ss_family, get_in_addr((struct sockaddr*)&connector_addrs), buf, sizeof buf);
        printf("server: got connection from %s\n", buf);

        // fork一个子进程
        if ((child_pid = fork()) == 0) {
            close(listenfd); // 子进程不需要监听
            if (send(connetfd, message, strlen(message), 1) == -1) {
                perror("send");
            }
            // 处理完客服端请求
            close(connetfd);
            exit(0);
        }
        close(connetfd);
    }
    return 0;
}