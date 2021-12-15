#include <stdio.h>

int lower_one_mask(int n);

int main()
{
    printf("0x%.8X\n", lower_one_mask(17));
    return 0;
}

int lower_one_mask(int n)
{
    int x = (1 << (n - 1)) << 1;

    return x - 1;
}

