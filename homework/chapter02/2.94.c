#include <stdio.h>

typedef unsigned float_bits;

float_bits float_twice(float_bits f);

int main()
{

    float_bits denor = 0x00400001;
    float *fp = (float *) &denor;

    printf("%.8x\n", float_twice(denor));
    *fp *= 2;
    printf("%.8x\n", denor);

    printf("%.8x\n", float_twice(denor));
    *fp *= 2;
    printf("%.8x\n", denor); 

    return 0;
}

float_bits float_twice(float_bits f)
{
    unsigned sign = f >> 31;
    unsigned exp = (f >> 23) & 0xff;
    unsigned frac = f & 0x7fffff;

    if (exp == 0xff && frac)
        return f;

    if (!exp) {
        // denormalized
        if (frac & 0x400000)
            ++exp;

        frac <<= 1;
    } else if (exp < 0xfe) {
        // normalized
        ++exp;
    } else {
        // INF
        exp = 0xff;
        frac = 0;
    }
    
    return (sign << 31) | (exp << 23) | frac;
}

