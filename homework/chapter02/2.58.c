#include "show_bytes.h"

int is_little_endian();

int main()
{
    printf("%d\n", is_little_endian());

    return 0;
}

int is_little_endian()
{
    int a = 1;

    byte_pointer p = (byte_pointer) &a;

    return *p;
}

