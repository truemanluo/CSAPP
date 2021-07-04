#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <signal.h>
#include <errno.h>
#include <arpa/inet.h>
#include <string.h>

#define PORT "3490"
#define MAXANSSIZE 200

void *get_in_addr(struct sockaddr *sa)
{
    if (sa->sa_family == AF_INET) {
        return &(((struct sockaddr_in*)sa)->sin_addr);
    }
    return &(((struct sockaddr_in6*)sa)->sin6_addr);
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "usage: hostname\n");
        exit(1);
    }
    struct addrinfo hints, *res, *p;
    char buf[INET6_ADDRSTRLEN];
    char ans[MAXANSSIZE];


    memset(&hints, 0, sizeof hints);

    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;

    int addrinfo_status;
    if ((addrinfo_status = getaddrinfo(argv[1], PORT, &hints, &res)) != 0) {
        fprintf(stderr, "cannot get address info %s.\n", gai_strerror(addrinfo_status));
    }

    int clientfd;

    // 遍历结果
    for (p = res; p != NULL; p = p->ai_next) {
        // 尝试分配socket
        if ((clientfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1) {
            perror("client: socket\n");
            continue;
        }

        // 尝试连接
        if (connect(clientfd, p->ai_addr, p->ai_addrlen) == -1) {
            // 连接失败则关闭clientfd
            close(clientfd);
            perror("client: connect\n");
            continue;
        }
        break;


    }

    if (p == NULL) {
        fprintf(stderr, "connect failed.\n");
        exit(1);
    }

    inet_ntop(p->ai_family, get_in_addr((struct sockaddr*)&p->ai_addr), buf, sizeof buf);

    printf("client: connecting to %s\n", buf);
    freeaddrinfo(res);

    // 如何获取服务器返回的connected fd?
    // recv
    int num_bytes;
    if ((num_bytes = recv(clientfd, ans, MAXANSSIZE-1, 0)) == -1) {
        perror("receive\n");
        exit(1);
    }

    ans[num_bytes-1] = '\0';
    printf("client: received '%s'\n",ans);
    close(clientfd);

    return 0;
}