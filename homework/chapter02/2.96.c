#include <stdio.h>

typedef unsigned float_bits;

int float_f2i(float_bits f);

int main()
{
    float f = 123.32199;
    int i = (int) f;
    float_bits *p = (float_bits *) &f;

    printf("%d\t%d\n", i, float_f2i(*p));
    return 0;
}

int float_f2i(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xff;
    unsigned frac = f & 0x7fffff;
    unsigned bias = (1 << 7) - 1;
    int bits_move;

    if (!exp)
        // denormalized equals 0
        return 0;

    bits_move = exp - bias - 23;

    // normalized appends 1
    frac |= 1 << 23;

    if (bits_move < 0) {
        if (bits_move < -24)
            frac = 0;
        else
            frac >>= bits_move * -1;
    } else {
        if (bits_move > 7)
            frac = 0x80000000;
        else
            frac <<= bits_move;
    }

    if (frac & sign)
        // frac not 0 and f is negative
        // frac could be int, and frac = -frac;
        frac = ~frac + 1;

    return (int) frac;
}

