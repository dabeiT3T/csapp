#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define ARRAY_LEN 1000000
#define X_VALUE 1.00000034524

double baseTime;

double poly(double a[], double x, long degree);
double polyh(double a[], double x, long degree);
double poly2x1a(double a[], double x, long degree);
double poly3x1a(double a[], double x, long degree);
double poly4x1a(double a[], double x, long degree);
double poly5x1a(double a[], double x, long degree);
double poly6x1a(double a[], double x, long degree);
double poly7x1a(double a[], double x, long degree);
double poly8x1a(double a[], double x, long degree);
double poly2x2(double a[], double x, long degree);
double poly3x3(double a[], double x, long degree);
double poly4x4(double a[], double x, long degree);
double poly5x5(double a[], double x, long degree);
double poly6x6(double a[], double x, long degree);
double poly7x7(double a[], double x, long degree);
double poly8x8(double a[], double x, long degree);
double poly9x9(double a[], double x, long degree);
double poly10x10(double a[], double x, long degree);
double poly4x2a(double a[], double x, long degree);
double poly6x2a(double a[], double x, long degree);
double poly6x3a(double a[], double x, long degree);
double poly8x2a(double a[], double x, long degree);
double poly8x4a(double a[], double x, long degree);
double poly9x3a(double a[], double x, long degree);
double poly12x3a(double a[], double x, long degree);
double poly12x4a(double a[], double x, long degree);
double poly12x6a(double a[], double x, long degree);

int main()
{
    int i;
    double a[ARRAY_LEN];
    double x = X_VALUE;
    double tmp = 1.000876;

    for (i = 0; i < ARRAY_LEN; i++) {
        a[i] = i + tmp;
        tmp *= 0.825;
    }

    poly(a, x, ARRAY_LEN-1);
    polyh(a, x, ARRAY_LEN-1);
    printf("----------------\n");
    poly2x1a(a, x, ARRAY_LEN-1);
    poly3x1a(a, x, ARRAY_LEN-1);
    poly4x1a(a, x, ARRAY_LEN-1);
    poly5x1a(a, x, ARRAY_LEN-1);
    poly6x1a(a, x, ARRAY_LEN-1);
    poly7x1a(a, x, ARRAY_LEN-1);
    poly8x1a(a, x, ARRAY_LEN-1);
    printf("----------------\n");
    poly2x2(a, x, ARRAY_LEN-1);
    poly3x3(a, x, ARRAY_LEN-1);
    poly4x4(a, x, ARRAY_LEN-1);
    poly5x5(a, x, ARRAY_LEN-1);
    poly6x6(a, x, ARRAY_LEN-1);
    poly7x7(a, x, ARRAY_LEN-1);
    poly8x8(a, x, ARRAY_LEN-1);
    poly9x9(a, x, ARRAY_LEN-1);
    poly10x10(a, x, ARRAY_LEN-1);
    printf("----------------\n");
    poly4x2a(a, x, ARRAY_LEN-1);
    poly6x2a(a, x, ARRAY_LEN-1);
    poly6x3a(a, x, ARRAY_LEN-1);
    poly8x2a(a, x, ARRAY_LEN-1);
    poly8x4a(a, x, ARRAY_LEN-1);
    poly9x3a(a, x, ARRAY_LEN-1);
    poly12x3a(a, x, ARRAY_LEN-1);
    poly12x4a(a, x, ARRAY_LEN-1);
    poly12x6a(a, x, ARRAY_LEN-1);
    
    return 0;
}

double poly(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr = x; /* Equals x^i at start of loop */

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= degree; i++) {
        result += a[i] * xpwr;
        xpwr *= x;
    }
    clock_gettime(CLOCK_REALTIME, &end);
    baseTime = end.tv_nsec-start.tv_nsec;
    printf(
        "poly\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/baseTime,
        result
    );
    return result;
}

double polyh(double a[], double x, long degree)
{
    long i;
    double result = a[degree];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = degree-1; i >= 0; i--)
        result = a[i] + x*result;

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "polyh\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}


double poly2x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr = xpwr0 * x;
    long limit = degree - 1;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=2) {
        result += xpwr0 * (a[i] + x * a[i+1]);
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly2x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );
    return result;
}

double poly3x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr = xpwr1 * x;
    long limit = degree - 2;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=3) {
        result += xpwr0 * (a[i] + x * a[i+1] + xpwr1 * a[i+2]);
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly3x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}

double poly4x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr = xpwr2 * x;
    long limit = degree - 3;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=4) {
        result += xpwr0 * (a[i] + x * a[i+1] + xpwr1 * a[i+2] + xpwr2 * a[i+3]);
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly4x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}

double poly5x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr = xpwr3 * x;
    long limit = degree - 4;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=5) {
        result += xpwr0 * (
            a[i] + x * a[i+1] +
            xpwr1 * a[i+2] +
            xpwr2 * a[i+3] +
            xpwr3 * a[i+4]
        );
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly5x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}

double poly6x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr = xpwr4 * x;
    long limit = degree - 5;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=6) {
        result += xpwr0 * (
            a[i] + x * a[i+1] +
            xpwr1 * a[i+2] +
            xpwr2 * a[i+3] +
            xpwr3 * a[i+4] +
            xpwr4 * a[i+5]
        );
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly6x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}

double poly7x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr = xpwr5 * x;
    long limit = degree - 6;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=7) {
        result += xpwr0 * (
            a[i] + x * a[i+1] +
            xpwr1 * a[i+2] +
            xpwr2 * a[i+3] +
            xpwr3 * a[i+4] +
            xpwr4 * a[i+5] +
            xpwr5 * a[i+6]
        );
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly7x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}

double poly8x1a(double a [], double x, long degree)
{
    long i;
    double result = a[0];
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr6 = xpwr5 * x;
    double xpwr = xpwr6 * x;
    long limit = degree - 7;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=8) {
        result += xpwr0 * (
            a[i] + x * a[i+1] +
            xpwr1 * a[i+2] +
            xpwr2 * a[i+3] +
            xpwr3 * a[i+4] +
            xpwr4 * a[i+5] +
            xpwr5 * a[i+6] +
            xpwr6 * a[i+7]
        );
        xpwr0 *= xpwr;
    }

    for (; i <= degree; i++) {
        result += a[i] * xpwr0;
        xpwr0 *= x;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly8x1a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result
    );

    return result;
}

double poly2x2(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr = xpwr1;
    long limit = degree - 1;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=2) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly2x2\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly3x3(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr = xpwr2;
    long limit = degree - 2;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=3) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly3x3\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly4x4(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr = xpwr3;
    long limit = degree - 3;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=4) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly4x4\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly5x5(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr = xpwr4;
    long limit = degree - 4;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=5) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        result4 += a[i+4] * xpwr4;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly5x5\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly6x6(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr = xpwr5;
    long limit = degree - 5;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=6) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        result4 += a[i+4] * xpwr4;
        result5 += a[i+5] * xpwr5;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
        xpwr5 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4 + result5;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly6x6\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly7x7(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double result6 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr6 = xpwr5 * x;
    double xpwr = xpwr6;
    long limit = degree - 6;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=7) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        result4 += a[i+4] * xpwr4;
        result5 += a[i+5] * xpwr5;
        result6 += a[i+6] * xpwr6;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
        xpwr5 *= xpwr;
        xpwr6 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4 + result5 + result6;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly7x7\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly8x8(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double result6 = 0;
    double result7 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr6 = xpwr5 * x;
    double xpwr7 = xpwr6 * x;
    double xpwr = xpwr7;
    long limit = degree - 7;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=8) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        result4 += a[i+4] * xpwr4;
        result5 += a[i+5] * xpwr5;
        result6 += a[i+6] * xpwr6;
        result7 += a[i+7] * xpwr7;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
        xpwr5 *= xpwr;
        xpwr6 *= xpwr;
        xpwr7 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4 + result5 + result6 + result7;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly8x8\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly9x9(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double result6 = 0;
    double result7 = 0;
    double result8 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr6 = xpwr5 * x;
    double xpwr7 = xpwr6 * x;
    double xpwr8 = xpwr7 * x;
    double xpwr = xpwr8;
    long limit = degree - 8;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=9) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        result4 += a[i+4] * xpwr4;
        result5 += a[i+5] * xpwr5;
        result6 += a[i+6] * xpwr6;
        result7 += a[i+7] * xpwr7;
        result8 += a[i+8] * xpwr8;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
        xpwr5 *= xpwr;
        xpwr6 *= xpwr;
        xpwr7 *= xpwr;
        xpwr8 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4 + result5 + result6 + result7 + result8;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly9x9\t\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly10x10(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double result6 = 0;
    double result7 = 0;
    double result8 = 0;
    double result9 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x;
    double xpwr2 = xpwr1 * x;
    double xpwr3 = xpwr2 * x;
    double xpwr4 = xpwr3 * x;
    double xpwr5 = xpwr4 * x;
    double xpwr6 = xpwr5 * x;
    double xpwr7 = xpwr6 * x;
    double xpwr8 = xpwr7 * x;
    double xpwr9 = xpwr8 * x;
    double xpwr = xpwr9;
    long limit = degree - 9;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=10) {
        result0 += a[i] * xpwr0;
        result1 += a[i+1] * xpwr1;
        result2 += a[i+2] * xpwr2;
        result3 += a[i+3] * xpwr3;
        result4 += a[i+4] * xpwr4;
        result5 += a[i+5] * xpwr5;
        result6 += a[i+6] * xpwr6;
        result7 += a[i+7] * xpwr7;
        result8 += a[i+8] * xpwr8;
        result9 += a[i+9] * xpwr9;
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
        xpwr5 *= xpwr;
        xpwr6 *= xpwr;
        xpwr7 *= xpwr;
        xpwr8 *= xpwr;
        xpwr9 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4 + result5 + result6 + result7 + result8 + result9;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly10x10\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );

    return result0;
}

double poly4x2a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x * x;
    double xpwr = xpwr1 * x;
    long limit = degree - 3;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=4) {
        result0 += xpwr0 * (a[i] + x * a[i+1]);
        result1 += xpwr1 * (a[i+2] + x * a[i+3]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly4x2a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly6x2a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xpwr1 = xpwr0 * x; // x^2
    double xpwr2 = xpwr1 * xpwr1; // x^4
    double xpwr = xpwr1 * xpwr2; // x^6
    long limit = degree - 5;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=6) {
        result0 += xpwr0 * (a[i] + x * a[i+1] + xpwr1 * a[i+2]);
        result1 += xpwr2 * (a[i+3] + x * a[i+4] + xpwr1 * a[i+5]);
        xpwr0 *= xpwr;
        xpwr2 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly6x2a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly6x3a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x; // x^2
    double xpwr1 = xpwr0 * xx; // x^3
    double xpwr2 = xpwr1 * xx; // x^5
    double xpwr = xpwr2 * x; // x^6
    long limit = degree - 5;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=6) {
        result0 += xpwr0 * (a[i] + x * a[i+1]);
        result1 += xpwr1 * (a[i+2] + x * a[i+3]);
        result2 += xpwr2 * (a[i+4] + x * a[i+5]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly6x3a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly8x2a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x; // x^2
    double xxx = xx * x; // x^3
    double xpwr1 = xxx * xx; // x^5
    double xpwr = xpwr1 * xxx; // x^8
    long limit = degree - 7;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=8) {
        result0 += xpwr0 * (a[i] + x * a[i+1] + xx * a[i+2] + xxx * a[i+3]);
        result1 += xpwr1 * (a[i+4] + x * a[i+5] + xx * a[i+6] + xxx * a[i+7]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly8x2a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly8x4a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x;
    double xpwr1 = xx * x; // x^3
    double xpwr2 = xpwr1 * xx; // x^5
    double xpwr3 = xpwr2 * xx; // x^7
    double xpwr = xpwr3 * x; // x^8
    long limit = degree - 7;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=8) {
        result0 += xpwr0 * (a[i] + x * a[i+1]);
        result1 += xpwr1 * (a[i+2] + x * a[i+3]);
        result2 += xpwr2 * (a[i+4] + x * a[i+5]);
        result3 += xpwr3 * (a[i+6] + x * a[i+7]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly8x4a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly9x3a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x; // x^2
    double xpwr1 = xx * xx; // x^4
    double xpwr2 = xpwr1 * xx * x; // x^7
    double xpwr = xpwr2 * xx; // x^9
    long limit = degree - 8;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=9) {
        result0 += xpwr0 * (a[i] + x * a[i+1] + xx * a[i+2]);
        result1 += xpwr1 * (a[i+3] + x * a[i+4] + xx * a[i+5]);
        result2 += xpwr2 * (a[i+6] + x * a[i+7] + xx * a[i+8]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly9x3a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly12x3a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x; // x^2
    double xxx = xx * x; // x^3
    double xpwr1 = xxx * xx; // x^5
    double xpwr2 = xpwr1 * xxx * x; // x^9
    double xpwr = xpwr2 * xxx; // x^12
    long limit = degree - 11;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=12) {
        result0 += xpwr0 * (a[i] + x * a[i+1] + xx * a[i+2] + xxx * a[i+3]);
        result1 += xpwr1 * (a[i+4] + x * a[i+5] + xx * a[i+6] + xxx * a[i+7]);
        result2 += xpwr2 * (a[i+8] + x * a[i+9] + xx * a[i+10] + xxx * a[i+11]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly12x3a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly12x4a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x; // x^2
    double xxx = xx * x; // x^3
    double xpwr1 = xpwr0 * xxx; // x^4
    double xpwr2 = xpwr1 * xxx; // x^7
    double xpwr3 = xpwr2 * xxx; // x^10
    double xpwr = xpwr3 * xx; // x^12
    long limit = degree - 11;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=12) {
        result0 += xpwr0 * (a[i] + x * a[i+1] + xx * a[i+2]);
        result1 += xpwr1 * (a[i+3] + x * a[i+4] + xx * a[i+5]);
        result2 += xpwr2 * (a[i+6] + x * a[i+7] + xx * a[i+8]);
        result3 += xpwr3 * (a[i+9] + x * a[i+10] + xx * a[i+11]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly12x4a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

double poly12x6a(double a [], double x, long degree)
{
    long i;
    double result0 = a[0];
    double result1 = 0;
    double result2 = 0;
    double result3 = 0;
    double result4 = 0;
    double result5 = 0;
    double xpwr0 = x; /* Equals x^i at start of loop */
    double xx = x * x; // x^2
    double xpwr1 = xpwr0 * xx; // x^3
    double xpwr2 = xpwr1 * xx; // x^5
    double xpwr3 = xpwr2 * xx; // x^7
    double xpwr4 = xpwr3 * xx; // x^9
    double xpwr5 = xpwr4 * xx; // x^11
    double xpwr = xpwr5 * x; // x^12
    long limit = degree - 11;

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    for (i = 1; i <= limit; i+=12) {
        result0 += xpwr0 * (a[i] + x * a[i+1]);
        result1 += xpwr1 * (a[i+2] + x * a[i+3]);
        result2 += xpwr2 * (a[i+4] + x * a[i+5]);
        result3 += xpwr3 * (a[i+6] + x * a[i+7]);
        result4 += xpwr4 * (a[i+8] + x * a[i+9]);
        result5 += xpwr5 * (a[i+10] + x * a[i+11]);
        xpwr0 *= xpwr;
        xpwr1 *= xpwr;
        xpwr2 *= xpwr;
        xpwr3 *= xpwr;
        xpwr4 *= xpwr;
        xpwr5 *= xpwr;
    }

    for (; i <= degree; i++) {
        result0 += a[i] * xpwr0;
        xpwr0 *= x;
    }

    result0 += result1 + result2 + result3 + result4 + result5;
    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "poly12x5a\t%9ld(%.2lfx):\t%lf\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        result0
    );
    return result0;
}

//
// Intel Xeon(Skylake) Platinum 8163
// 8vCPU 8GiB
// Centos 7.8
//
// gcc -Og -mavx2 5.18.c -o 5.18 && ./5.18
//
// poly          3380954(1.00x):   631454548160.117310
// polyh         4886367(0.69x):   631454548160.108887
// ----------------
// poly2x1a      1711412(1.98x):   631454548170.339355
// poly3x1a      1164472(2.90x):   631454548180.585327
// poly4x1a       859251(3.93x):   631454548166.764404
// poly5x1a       694615(4.87x):   631454548162.592896
// poly6x1a       585700(5.77x):   631454548163.157349
// poly7x1a       607349(5.57x):   631454548166.517212
// poly8x1a       634687(5.33x):   631454548171.590210
// ----------------
// poly2x2       1716023(1.97x):   631454548170.337524
// poly3x3       1205678(2.80x):   631454548180.579590
// poly4x4        893099(3.79x):   631454548166.774048
// poly5x5        786363(4.30x):   631454548162.572754
// poly6x6        725785(4.66x):   631454548163.166992
// poly7x7        567913(5.95x):   631454548166.527466
// poly8x8        578621(5.84x):   631454548171.570068
// poly9x9        594496(5.69x):   631454548167.081543
// poly10x10      589430(5.74x):   631454548165.524414
// ----------------
// poly4x2a       887593(3.81x):   631454548166.762207
// poly6x2a       628840(5.38x):   631454548163.154419
// poly6x3a       611384(5.53x):   631454548179.182373
// poly8x2a       581303(5.82x):   631454548183.581299
// poly8x4a       610031(5.54x):   631454548183.589111
// poly9x3a       553854(6.10x):   631454548167.086182
// poly12x3a      549039(6.16x):   631454548176.283203
// poly12x4a      538230(6.28x):   631454548176.271240
// poly12x5a      576508(5.86x):   631454548176.273193
//
// poly12x3a or poly12x4a might be the best way.
//
