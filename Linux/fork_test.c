#include <stdio.h>

int main()
{
    printf("My PId is %d\n", getpid());
    fork();
    fork();
    fork();
    printf("My PId is %d\n", getpid());
    return 0;
}