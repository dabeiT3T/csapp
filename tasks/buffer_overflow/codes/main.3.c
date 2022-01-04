#include <stdio.h>

char *mgets(char *s);
void echo();
void hack();

int main()
{
    echo();

    return 0;
}

char *mgets(char *s)
{
    /* Get func addr */
    void (*fp)();
    fp = hack;
    /* Update return addr */
    unsigned long *ret = (unsigned long *) (s+24);
    *ret = (unsigned long) fp;

    return s;
}

void echo()
{
    char buf[8]; // Way too small!
    mgets(buf);
    puts(buf);
}

void hack()
{
    printf("Oops, U are hacked!\n");
}
