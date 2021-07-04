#include <stdio.h>
typedef unsigned char* byte_pointer;

// unsigned char是整型，在计算机中以补码形式存储
void show_bytes(byte_pointer p, size_t len)
{
    size_t i;
    for (i = 0; i < len; ++i) {
        printf("%.2x\n", p[i]);
    }
}

void show_int(int a)
{
    show_bytes((byte_pointer) &a, sizeof(a));
}

int main()
{
    int a = 12345;
    show_int(a);
    return 0;
}