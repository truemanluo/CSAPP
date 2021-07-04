#include <stdio.h>

void inplace_swap(int *p, int *q)
{
    *p = *p ^ *q;
    *q = *q ^ *p;
    *p = *p ^ *q;
}

int main()
{
    int a = 1, b = 2;
    int word = 0x876543;
    int mask = 0xFF;
    int ans1 = word & mask;
    int ans2 = word | mask;
    int ans3 = ~word ^ mask;
    printf("ans1: %.x\nans2: %.x\nans3: %.x\n", ans1, ans2, ans3);
    return 0;
}