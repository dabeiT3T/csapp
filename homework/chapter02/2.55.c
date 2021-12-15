#include "show_bytes.h"

int main()
{

    int a = 0x12345678;

    show_bytes((byte_pointer) &a, sizeof(a));

    return 0;
}

