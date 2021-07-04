#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
    char *arglist[3];
    arglist[0] = "ls";
    arglist[1] = "-l";
    arglist[2] = NULL;
    printf("***About exevcvp.***\n");
    execvp("ls", arglist);
}