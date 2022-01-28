#include <stdio.h>

int signed_high_prod(int x, int y);
unsigned unsigned_high_prod(unsigned x, unsigned y);

int main()
{
    unsigned x = 0x12345678;
    unsigned y = 0x87654321;
    printf("%x%x\n", unsigned_high_prod(x, y), x * y);
    printf("%lx\n", (long) x * y);

    return 0;
}

/*
 * This should be a lib function,
 * so that it's ok we use long int and multiplication.
 */
int signed_high_prod(int x, int y)
{
    return ((long) x * y) >> (sizeof(int) << 3);
}

unsigned unsigned_high_prod(unsigned x, unsigned y)
{
    int move = (sizeof(x) << 3) - 1;
    int mask_x = (int) x >> move;
    int mask_y = (int) y >> move;
    return signed_high_prod(x, y) + (mask_x & y) + (mask_y & x);
}

