#include <stdio.h>

int mul3div4(int x);

int main()
{
    printf("%d\n", mul3div4(-21));
    return 0;
}

int mul3div4(int x)
{
    x = (x << 1) + x;
    int size = sizeof(int) << 3;
    int mask = x >> size - 1;
    return x + (mask & 3) >> 2;
}

