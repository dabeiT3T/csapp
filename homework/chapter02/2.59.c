#include <stdio.h>

int main()
{

    int x = 0x89abcdef;
    int y = 0x76543210;

    printf("0x%X\n", (x & 0xff) | (y & ~0xff));

    return 0;
}

