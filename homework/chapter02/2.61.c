#include <stdio.h>

int is_all_one(int x);
int is_all_zero(int x);
int is_lsb_one(int x);
int is_msb_zero(int x);

int main()
{
    printf("%d\n", is_all_one(~0));
    printf("%d\n", is_all_zero(0x0));
    printf("%d\n", is_lsb_one(0x0f));
    printf("%d\n", is_msb_zero(0x123456));

    return 0;
}

int is_all_one(int x)
{
    return !~x;
}

int is_all_zero(int x)
{
    return !x;
}

int is_lsb_one(int x)
{
    return !(x & 0xff ^ 0xff);
}

int is_msb_zero(int x)
{
    return !(x >> ((sizeof(int) - 1) << 3));
}

