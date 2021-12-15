#include <stdio.h>

unsigned rotate_left(unsigned x, int n);

int main()
{
    unsigned x = 0x12345678;
    printf("0x%.8X 0x%.8X\n", x, rotate_left(x, 0));

    return 0;
}

unsigned rotate_left(unsigned x, int n)
{
    unsigned right = x >> ((sizeof(unsigned) << 3) - n - 1) >> 1;
    x <<= n;

    return x | right;
}

