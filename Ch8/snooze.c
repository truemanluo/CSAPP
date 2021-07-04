#include <stdio.h>
#include <unistd.h>

unsigned int snooze(unsigned int secs)
{
    unsigned int secleft = sleep(secs);
    printf("Slept for %i of %i\n", secs-secleft, secs);
    return secleft;
}

int main()
{
    snooze(20);
    return 0;
}