#include <stdio.h>

typedef unsigned packed_t;

int xbyte(packed_t word, int bytenum);

int main()
{

    printf("%d\n", xbyte(0x8f0fff9a, 0));

    return 0;
}

int xbyte(packed_t word, int bytenum)
{
    int x = (word >> (bytenum << 3)) & 0xff;
    printf("%0.2x\n", x);
    return x - ((x & 0x80) << 1);
}

