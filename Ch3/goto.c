#include <stdio.h>

int main()
{
    int n = 1;
    if (n == 1) {
        goto Next;
    }
    printf("Hello");
    Next:
        n += 5;
        printf("%d:\n", n);
    NextNext:
        n += 6;
        printf("%d:\n", n);
    return 0;
}

