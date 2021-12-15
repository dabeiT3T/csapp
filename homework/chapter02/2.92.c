#include <stdio.h>

typedef unsigned float_bits;

float_bits float_negate(float_bits f);

int main()
{
    float f = 1.2345;
    float_bits *p = (float_bits *) &f;
    float_bits neg = float_negate(*p);
    float *pf = (float *) &neg;

    printf("%f %f\n", -f, *pf);

    return 0;
}

float_bits float_negate(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0xff && frac)
        return f;

    return f ^ 0x80000000;
}

