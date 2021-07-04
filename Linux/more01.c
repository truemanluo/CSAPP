#include <stdio.h>
#include <stdlib.h>

// 定义页长和每行字符的长度
#define PAGELEN 24
#define LINELEN 512

// 显示一页
void do_more(FILE *fp);
// 输出一页后根据用户输入决定下一步操作
int see_more();

int main(int argc, char *argv[])
{
    if (argc == 1) {
        printf("more: bad usage\n");
        printf("Try \'more --help\' for more information.\n");
    }
    // 读取文件
    else {
        FILE *fp;
        while (--argc) {
            // 文件读取成功
            if ((fp = fopen(*++argv, "r")) != NULL) {
                // 将任务交给do_more
                do_more(fp);
                fclose(fp);
            }
            else {
                exit(1);
            }
        }
    }
    return 0;
}

void do_more(FILE *fp)
{
    // 先显示一屏幕
    char contents[LINELEN];
    int cnt = 0;
    while (fgets(contents, LINELEN, fp)) {
        // 打印
        if (fputs(contents, stdout) == EOF) exit(1);
        int reply;
        if (cnt == PAGELEN) {
            // 如果回车，则输出一行，并继续等待用户指令
            reply = see_more();
            if (reply == 0) break;
            cnt -= reply;
        }
        ++cnt;
    }

}

int see_more()
{
    // 一直等待用户输入
    int c;
    printf("\033[7m more?\033[m");
    while ((c = getchar()) != EOF) {
        if (c == 'q') {
            return 0;
        }
        if (c == ' ') {
            return PAGELEN;
        }
        if (c == '\n') {
            return 1;
        }
    }
    return 0;
}