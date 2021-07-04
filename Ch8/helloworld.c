#include <unistd.h>

int main()
{
    while (1)
        write(1, "hello, world\n", 13);
    _exit(0);
}