#include <stdio.h>

int divide_power2(int x, int k);

int main()
{

    printf("%d\n", divide_power2(-10, 2));

    return 0;
}

int divide_power2(int x, int k)
{
    int mask = x >> ((sizeof(int) << 3) - 1);
    x += mask & ((1 << k) - 1);

    return x >> k;
}

