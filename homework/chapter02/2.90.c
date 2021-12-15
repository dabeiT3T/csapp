#include <stdio.h>

float u2f(unsigned int x);
float fpwr2(int x);

int main()
{
    int x;
    scanf("%d", &x);
    printf("%.0f\n", fpwr2(x));
    return 0;
}

float u2f(unsigned int x)
{
    float *p = (float *) &x;
    return *p;
}

float fpwr2(int x)
{
    unsigned exp, frac;
    unsigned u;

    if (x < -149) {
        /* Too small. Return 0.0 */
        exp = 0;
        frac = 0;
    } else if (x < -126) {
        /* Denormalized result */
        exp = 0;
        frac = 1 << x + 149;
    } else if (x < 128) {
        /* Normalized result. */
        exp = x + 127;
        frac = 0;
    } else {
        /* Too big. Return +oo */
        exp = 0xff;
        frac = 0;
    }

    u = exp << 23 | frac;
    return u2f(u);
}

