#include <stdio.h>

int bad_int_size_is_32();

int main()
{
    printf("%d\n", bad_int_size_is_32());
    printf("%d\n", int_size_is_32());

    return 0;
}

int int_size_is_32()
{
   int set_msb = 1 << 128;
   return set_msb >> 128 == -1;
}

int bad_int_size_is_32()
{
    int set_msb = 1 << 31;
    int beyond_msb = 1 << 32;

    return set_msb && !beyond_msb;
}

