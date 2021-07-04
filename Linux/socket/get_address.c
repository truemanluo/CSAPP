#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>

// addrinfo
#include <netdb.h>

int main() 
{
    // 当前我为服务器，监听我主机的socket(IP:3490)
    int status;
    struct addrinfo hints;
    struct addrinfo *servinfo; // 指向结果

    memset(&hints, 0, sizeof hints); // 将&hints以后的（sizeof hints）设为空
    hints.ai_family = AF_UNSPEC; // IPV4 or IPV6
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE; // 为我填充IP

    if ((status = getaddrinfo(NULL, "3490", &hints, &servinfo)) != 0) {
        // 出错
        fprintf(stderr, "getaddrinfo error: %s\n", gai_strerror(status));
        exit(1);
    }
    // 现在servinfo指向一个addrinfo的LinkedList
    
    // do something

    // 释放linked-list
    freeaddrinfo(servinfo);

    return 0;
}