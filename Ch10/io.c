#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

// int open(char *filename, int flags, mode_t mode);
/**
 * fd: 文件描述符
 * buf: 缓冲区
 * n: 程序期望每次读入的大小
 **/

ssize_t rio_readn(int fd, char* buf, size_t n);



int main()
{
    int a, b = 5;
    // if ((a = 7) > b) {
        printf("%d", a);
    // }
    return 0;
}