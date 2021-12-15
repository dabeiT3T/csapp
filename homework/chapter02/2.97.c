#include <stdio.h>

typedef unsigned float_bits;

float_bits float_i2f(int i);

int main()
{
    int i = -0xfffffe9;
    float_bits fb = float_i2f(i);
    float *pf = (float *) &fb;
    float f = (float) i;
    printf("int: %d\nmy float: %f\nfloat convert: %f\n", i, *pf, f);

    return 0;
}

float_bits float_i2f(int i)
{
    if (!i)
        return 0;

    unsigned sign = (i >> 31) != 0;
    // using -O1 above and below sign have the same compile
    // which is using shr to get the sign.
    // unsigned sign = i >= 0 ? 0 : 1;

    // we get the positive part, -i is ok if i < 0
    unsigned frac = sign ? ~(i - 1) : i;
    unsigned exp;
    unsigned round, above;
    unsigned bias = (1 << 7) - 1;
    int move_bits;
    int j;

    // find first 1
    for (j = 30; j >= 0; --j) {
        if ((1 << j) & frac)
            break;
    }

    move_bits = j - 23;

    if (move_bits <= 0)
        frac <<= -move_bits;
    else {
        // round to even
        // move out: 1011(above 1000) => round
        above = ((1 << move_bits) - 1) > (1 << move_bits - 1);
        // move out: 1000 and the lowest unmoved-out bit is 1 => round
        round = (frac >> move_bits) & (frac >> move_bits - 1) & 1;
        // btw, even using if (above statment) else if (round statment) 
        // the compiler may use cmov, both statement will be executed
        // even if the compiler does not use cmov
        // this is better way because of the cpu piplines

        frac >>= move_bits;
        frac += above | round;
    }

    exp = j + bias + ((frac >> 24) & 1);
    frac &= 0x7fffff;

    return (sign << 31) | (exp << 23) | frac;
}

