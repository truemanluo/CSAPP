#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


// 定义命令的最大数量和单条命令的最大长度
#define ARGLEN 10
#define ARGNUM 10

char* make_string(char str[]);
int main()
{
    // 从控制台读入命令
    char *argv[ARGNUM];
    char argbuf[ARGLEN];
    int num_arg = 0;
    // 构造arglist

    while (num_arg < ARGNUM && fgets(argbuf, ARGLEN, stdin)) {
        printf("Arg[%d]? ", num_arg);
        if (*argbuf != '\n') {
            argv[num_arg++] = make_string(argbuf);
        }
        else {
    // 交由execvp执行
            // 判断是否有命令（第一次写时遗漏）
            if (num_arg > 0) {
                argv[num_arg] = NULL;
                execvp(argv[0], argv);
                perror("Exec failed");
                exit(1);
            }
            
        }
    }
    return 0;
}

char* make_string(char str[])
{
    // stdin会将换行符存入buffer中
    str[strlen(str)-1] = '\0';
    char *cp = (char *)malloc(strlen(str)+1);
    if (cp == NULL)
        fprintf(stderr, "No memory.");
    strcpy(cp, str);
    return cp;
}
