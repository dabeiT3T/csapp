#include <stdio.h>
#include "show_bytes.h"

void show_bytes(byte_pointer p, size_t size)
{
    size_t i;

    for (i = 0; i < size; ++i, ++p)
    {
        printf("%.2x", *p);
    }

    printf("\n");
}

