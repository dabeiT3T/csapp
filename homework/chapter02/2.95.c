#include <stdio.h>

typedef unsigned float_bits;

float_bits float_half(float_bits f);

int main()
{
    float_bits x = 0x00ffffff;
    float *pf = (float *) &x;

    printf("%.8x\n", float_half(x));
    *pf /= 2;
    printf("%.8x\n", x);

    return 0;
}

float_bits float_half(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xff;
    unsigned frac = f & 0x7fffff;

    unsigned bias = (frac & 1) & ((frac >> 1) & 1);

    if (exp == 0xff && frac)
        return f;

    if (!exp) {
        // denormalized
        frac >>= 1;
        frac += bias;
    } else if (exp < 0xff) {
        // normalized
        if (exp == 1) {
            frac >>= 1;
            frac |= 0x400000;
            frac += bias;
            // if frac == 0x7fffff
            // did code above frac = 0x800000(overflow)
            // exp is 0x1, but set by frac
        } else
            --exp;
    }
    // INF return INF
    return (sign << 31) | (exp << 23) | frac;
}

