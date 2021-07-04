#include <stdlib.h>
#include <stdio.h>

int main()
{
    char a[3];
    fgets(a, 3, stdin);
    int i;
    for (i = 0; i < 3; ++i)
        printf("%c", a[i]);
    return 0;
}