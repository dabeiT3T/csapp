#include <stdio.h>

char *mgets(char *s);
void echo();

int main()
{
    echo();

    return 0;
}

char *mgets(char *s)
{
    int c;
    char *dest = s;
    long *ret = (long *) (s + 24);

    printf("return addr is %x\n", *ret);

    return s;
}

void echo()
{
    char buf[8]; // Way too small!
    mgets(buf);
    puts(buf);
}
