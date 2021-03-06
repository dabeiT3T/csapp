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

    while ((c = getchar()) != '\n' && c != EOF)
        *dest++ = c;

    if (c == EOF && dest == s)
        /* No characters read */
        return NULL;

    *dest++ = '\0';
    return s;
}

void echo()
{
    char buf[8]; // Way too small!
    mgets(buf);
    puts(buf);
}
