#include <stdio.h>

int fits_bits(int x, int n);

int main()
{

    printf("%d\n", fits_bits(15, 5));

    return 0;
}

int fits_bits(int x, int n)
{
    return x <= ((1 << (n - 1)) - 1) && x >= ~((1 << (n - 1)) - 1);
}

int fits_bits(int x, int n)
{
    x >>= n - 1;
    return !x || !~x;
}

