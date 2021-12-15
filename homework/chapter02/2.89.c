#include <stdio.h>
#include <limits.h>

int main()
{
    // float a = 16777215;
    int b = 16777217;
    float a = (float) b;
    double c = (double) b;
    float d = (float) c;

    printf("%d %f %f %f\n", b, a, c, d);

    int x = INT_MAX;
    int y = INT_MIN;
    printf("%d\n", x - y);

    double e = INT_MAX;
    double f = INT_MAX-4;
    double g = 3;

    printf("%f %f\n", e*f*g, e*g*f);

    return 0;
}

