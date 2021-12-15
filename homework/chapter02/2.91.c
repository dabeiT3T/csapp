#include <stdio.h>

int main()
{
    int a = 0x40490fdb;
    float *p = (float *)&a;

    printf("%f\n%.20f\n", *p, *p);

    return 0;
}

// 11.00100100001111110110110
// 11.001001001[001]...
// 9

