#include <stdio.h>
#include <time.h>
#include <sys/time.h>

#define ARRAY_LEN 50000
double baseTime;

void psum1(float a[], float p[], long n);
void psum1a(float a[], float p[], long n);
void psum2(float a[], float p[], long n);
void psum2a(float a[], float p[], long n);
void psum3a(float a[], float p[], long n);
void psum4a(float a[], float p[], long n);
void psum5a(float a[], float p[], long n);
void psum6a(float a[], float p[], long n);

int main()
{
    int i;
    float a[ARRAY_LEN];
    float p[ARRAY_LEN];

    float tmp = 1.000876;

    for (i = 0; i < ARRAY_LEN; i++) {
        a[i] = i + tmp;
        p[i] = tmp * 2.13456;
        tmp *= 0.825;
    }

    psum1(a, p, ARRAY_LEN);
    psum1a(a, p, ARRAY_LEN);
    psum2(a, p, ARRAY_LEN);
    printf("----------------\n");
    psum2a(a, p, ARRAY_LEN);
    psum3a(a, p, ARRAY_LEN);
    psum4a(a, p, ARRAY_LEN);
    psum5a(a, p, ARRAY_LEN);
    psum6a(a, p, ARRAY_LEN);

    return 0;
}

void psum1(float a[], float p[], long n)
{
    long i;
    p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < n; i++)
        p[i] = p[i-1] + a[i];

    clock_gettime(CLOCK_REALTIME, &end);
    baseTime = end.tv_nsec-start.tv_nsec;
    printf(
        "psum1\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/baseTime,
        p[i-1]
    );
}

void psum1a(float a[], float p[], long n)
{
    long i;
    /* last_val holds p[i-1]; val holds p[i] */
    float last_val, val;
    last_val = p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < n; i++) {
        val = last_val + a[i];
        p[i] = val;
        last_val = val;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum1a\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        val
    );
}

void psum2(float a[], float p[], long n)
{
    long i;
    p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < n-1; i+=2) {
        float mid_val = p[i-1] + a[i];
        p[i] = mid_val;
        p[i+1] = mid_val + a[i+1];
    }

    /* For even n, finish remaining element */
    for (; i < n; i++)
        p[i] = p[i-1] + a[i];

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum2\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        p[i-1]
    );
}

void psum2a(float a[], float p[], long n)
{
    long i;
    long limit = n - 1;
    float mid_val0;
    float mid_val1;
    float last_val;
    last_val = p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < limit; i+=2) {
        mid_val0 = last_val + a[i];
        mid_val1 = mid_val0 + a[i+1];
        p[i] = mid_val0;
        p[i+1] = mid_val1;
        last_val += a[i] + a[i+1];
    }

    /* For even n, finish remaining element */
    for (; i < n; i++)
        p[i] = p[i-1] + a[i];

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum2a\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        p[i-1]
    );
}

void psum3a(float a[], float p[], long n)
{
    long i;
    long limit = n - 2;
    float mid_val0;
    float mid_val1;
    float mid_val2;
    float last_val;
    last_val = p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < limit; i+=3) {
        mid_val0 = last_val + a[i];
        mid_val1 = mid_val0 + a[i+1];
        mid_val2 = mid_val1 + a[i+2];
        p[i] = mid_val0;
        p[i+1] = mid_val1;
        p[i+2] = mid_val2;
        last_val += a[i] + a[i+1] + a[i+2];
    }

    /* For even n, finish remaining element */
    for (; i < n; i++)
        p[i] = p[i-1] + a[i];

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum3a\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        p[i-1]
    );
}

void psum4a(float a[], float p[], long n)
{
    long i;
    long limit = n - 3;
    float mid_val0;
    float mid_val1;
    float mid_val2;
    float mid_val3;
    float last_val;
    last_val = p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < limit; i+=4) {
        mid_val0 = last_val + a[i];
        mid_val1 = mid_val0 + a[i+1];
        mid_val2 = mid_val1 + a[i+2];
        mid_val3 = mid_val2 + a[i+3];
        p[i] = mid_val0;
        p[i+1] = mid_val1;
        p[i+2] = mid_val2;
        p[i+3] = mid_val3;
        last_val += a[i] + a[i+1] + (a[i+2] + a[i+3]);
    }

    /* For even n, finish remaining element */
    for (; i < n; i++) {
        mid_val0 = last_val + a[i];
        p[i] = mid_val0;
        last_val = mid_val0;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum4a\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        p[i-1]
    );
}

void psum5a(float a[], float p[], long n)
{
    long i;
    long limit = n - 4;
    float mid_val0;
    float mid_val1;
    float mid_val2;
    float mid_val3;
    float mid_val4;
    float last_val;
    last_val = p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < limit; i+=5) {
        mid_val0 = last_val + a[i];
        mid_val1 = mid_val0 + a[i+1];
        mid_val2 = mid_val1 + a[i+2];
        mid_val3 = mid_val2 + a[i+3];
        mid_val4 = mid_val3 + a[i+4];
        p[i] = mid_val0;
        p[i+1] = mid_val1;
        p[i+2] = mid_val2;
        p[i+3] = mid_val3;
        p[i+4] = mid_val4;
        last_val += a[i] + a[i+1] + (a[i+2] + a[i+3] + a[i+4]);
    }

    /* For even n, finish remaining element */
    for (; i < n; i++) {
        mid_val0 = last_val + a[i];
        p[i] = mid_val0;
        last_val = mid_val0;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum5a\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        p[i-1]
    );
}

void psum6a(float a[], float p[], long n)
{
    long i;
    long limit = n - 5;
    float mid_val0;
    float mid_val1;
    float mid_val2;
    float mid_val3;
    float mid_val4;
    float mid_val5;
    float last_val;
    last_val = p[0] = a[0];

    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    for (i = 1; i < limit; i+=6) {
        mid_val0 = last_val + a[i];
        mid_val1 = mid_val0 + a[i+1];
        mid_val2 = mid_val1 + a[i+2];
        mid_val3 = mid_val2 + a[i+3];
        mid_val4 = mid_val3 + a[i+4];
        mid_val5 = mid_val3 + a[i+5];
        p[i] = mid_val0;
        p[i+1] = mid_val1;
        p[i+2] = mid_val2;
        p[i+3] = mid_val3;
        p[i+4] = mid_val4;
        p[i+5] = mid_val5;
        last_val += a[i] + a[i+1] + (a[i+2] + a[i+3] + a[i+4] + a[i+5]);
    }

    /* For even n, finish remaining element */
    for (; i < n; i++) {
        mid_val0 = last_val + a[i];
        p[i] = mid_val0;
        last_val = mid_val0;
    }

    clock_gettime(CLOCK_REALTIME, &end);
    printf(
        "psum6a\t\t%9ld(%.2lfx):\t%f\n",
        end.tv_nsec-start.tv_nsec,
        baseTime/(end.tv_nsec-start.tv_nsec),
        p[i-1]
    );
}
