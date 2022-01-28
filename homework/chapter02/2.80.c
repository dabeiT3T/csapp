#include <stdio.h>

int threefourths(int x);

int main()
{
    int i;
    // some tests
    for (i = -10; i < 11; i++)
        printf("%d %d\n", (int)(0.75*i), threefourths(i));
    
    return 0;
}

int threefourths(int x)
{
    // it will not overflow, so we can't use << on x
    int mask = x >> (sizeof(int) << 3) - 1;
    // rounded to 0, add bias when x is positive
    int y = x - (x + (~mask & 3) >> 2);
    return y;
}

