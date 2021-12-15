#include <stdio.h>

unsigned replace_byte(unsigned x, int i, unsigned char b);

int main()
{
    printf("%X\n", replace_byte(0x12345678, 2, 0xab));
    printf("%X\n", replace_byte(0x12345678, 0, 0xab));

    return 0;
}

unsigned replace_byte(unsigned x, int i, unsigned char b)
{

    unsigned pre = (unsigned) b << (i << 3);
    unsigned umask = ~(0xff << (i << 3));

    return x & umask | pre;
}

