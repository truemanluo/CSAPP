#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[], char *envp[])
{
    printf("Commandline arguments:\n");
    int i = 0;
    while (i < argc) {
        printf("arg[%d]: %s\n", i, argv[i]);
        ++i;
    }
    printf("Environment variables:\n");
    i = 0;
    char **env = envp;
    while (env[i] != 0) {
        printf("envp[%d]: %s\n", i, env[i]);
        ++i;
    }
    return 0;
}