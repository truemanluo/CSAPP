#include <stdio.h>
#include <stdlib.h>

int plus(int a, int b)
{
    return a + b;
}

void add_store(int a, int b, int *dest)
{
    int c = plus(a, b);
    *dest = c;
}

int main(int argc, char* argv[])
{
    int a = atoi(argv[1]);
    int b = atoi(argv[2]);
    int dest;
    add_store(a, b, &dest);
    return 0;
}