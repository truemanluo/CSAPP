#include <stdio.h>
#include <stdbool.h>

bool is_equal(unsigned int a, unsigned int b)
{
    return (unsigned)((a^b)) == 0;
}

int main()
{
    unsigned int a = 2, b = 2, c = 3;
    printf("a == b: %u, a == c: %u", is_equal(a, b), is_equal(a, c));
}

