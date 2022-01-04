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
    int i;
    /* Get func addr */
    void (*fp)();
    fp = hack;
    /* Update return addr */
    unsigned long *ret = (long *) (s+24);

    printf("fp at %p %lu\n", fp, (unsigned long)fp);
    printf("s at %p %lu\n", s, (unsigned long)s);

    *ret = (unsigned long) s;

    /* binary code */
    /* movabsq &hack, %rax */
    s[0] = '\x48';
    s[1] = '\xb8';
    unsigned long *hack_addr = (unsigned long *) (s+2);
    *hack_addr = (unsigned long) fp;
    /* jmp %rax */
    s[10] = '\xff';
    s[11] = '\xe0';
    /* nop */
    for (i = 12; i < 24; ++i)
        s[i] = '\x90';

    for (i = 0; i < 32; ++i)
        printf("%2.2x ", s[i]);
    printf("\n");

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
