#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


// 定义命令的最大数量和单条命令的最大长度
#define ARGLEN 10
#define ARGNUM 10

char* make_string(char str[]);
void execute(char *argv[]);
int main()
{
    // 从控制台读入命令
    char *argv[ARGNUM];
    char argbuf[ARGLEN];
    int num_arg = 0;
    // 构造arglist

    while (num_arg < ARGNUM) {
        printf("Arg[%d]? ", num_arg);
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n') {
            argv[num_arg++] = make_string(argbuf);
        }
        else {
    // 交由execvp执行
            // 判断是否有命令（第一次写时遗漏）
            if (num_arg > 0) {
                argv[num_arg] = NULL;
                // execvp(argv[0], argv);
                // 执行
                execute(argv);
                // num_arg清零，继续执行
                num_arg = 0;
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
    if (cp == NULL) {
        fprintf(stderr, "No memory.");
        exit(1);
    }
    strcpy(cp, str);
    return cp;
}


void execute(char *argv[])
{
    int pid, exitstatus, curr_pid;
    pid = fork();
    if (pid == 0) {
        // 子进程
        execvp(argv[0], argv);
        perror("Exec failed");
        exit(1);
    }
    else if (pid == -1) {
        // 执行出错
        perror("Fork failed");
        exit(1);
    }
    else {
        // 父进程
        while ((curr_pid = wait(&exitstatus)) != pid) 
            // 等待当前子进程退出
            ;
        printf("Child process exited status: %d, %d, %d\n", exitstatus >> 8, exitstatus & 0x80, exitstatus &0x7f);
    }
}