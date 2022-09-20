#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <time.h>
#include <sys/time.h>

// in order to hit the cache, try to read more item in row
// read src[0][0], try to read src[0][1]
// write dst[0][0], try to write dst[0][1]
// if we split the matrix into block, eg 4*4
// src[0][0],src[1][0] miss, src[0][1],src[1][1] hit
// dst[0][0],dst[1][0] miss, dst[0][1],dst[1][1] hit
// the n of block larger, the more miss rate will reduce
// try `gcc -Og 6.45.c`

// matrix[N][N]
#define N 10125

void transpose(int *dst, int *src, int dim);
void opt_transpose(int (*dst)[N], int (*src)[N], int dim, int n);
void opt2_transpose(int (*dst)[N], int (*src)[N], int dim, int n);

int main()
{
    int buffSize = N*N*sizeof(int);
    int *src = (int *) malloc(buffSize);
    int *dst = (int *) malloc(buffSize);

    if (!src || !dst)
        return 1;

    // int fd = open("/dev/urandom", O_RDONLY);
    // read(fd, src, buffSize);
    // close (read);

    // warm up
    transpose(dst, src, N);
    // test, cache for each function may cause conflict
    transpose(dst, src, N);
    opt_transpose((int (*)[N]) dst, (int (*)[N]) src, N, 8);
    opt_transpose((int (*)[N]) dst, (int (*)[N]) src, N, 16);
    opt2_transpose((int (*)[N]) dst, (int (*)[N]) src, N, 8);
    opt2_transpose((int (*)[N]) dst, (int (*)[N]) src, N, 16);

    free(src);
    free(dst);
    return 0;
}

void transpose(int *dst, int *src, int dim)
{
    int i, j;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (i = 0; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[j*dim + i] = src[i*dim + j];

    gettimeofday(&end, NULL);
    printf(
        "transpose:\t%ld.%06ld\n",
        end.tv_sec-start.tv_sec,
        labs(end.tv_usec-start.tv_usec)
    );
}

void opt_transpose(int (*dst)[N], int (*src)[N], int dim, int n)
{
    int i, j, r, c, row, col;
    int limit = dim  / n;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (i = 0; i < limit; i++)
        for (j = 0; j < limit; j++)
            for (r = 0; r < n; r++)
                for (c = 0; c < n; c++) {
                    col = i * n + r;
                    row = j * n + c;
                    dst[row][col] = src[col][row];
                }

    r = i * n;
    // right elements left
    for (i = 0; i < r; i++)
        for (j = r; j < dim; j++)
            dst[j][i] = src[i][j];
    // buttom elements left
    for (i = r; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[j][i] = src[i][j];  

    gettimeofday(&end, NULL);
    printf(
        "opt_transpose:\t%ld.%06ld(block %d)\n",
        end.tv_sec-start.tv_sec,
        labs(end.tv_usec-start.tv_usec),
        n
    );
}

// n & 1 == 0
void opt2_transpose(int (*dst)[N], int (*src)[N], int dim, int n)
{
    int i, j, r, c, row, col;
    int limit = dim  / n;

    struct timeval start, end;
    gettimeofday(&start, NULL);

    for (i = 0; i < limit; i++)
        for (j = 0; j < limit; j++)
            for (r = 0; r < n; r++)
                for (c = 0; c < n; c+=2) {
                    col = i * n + r;
                    row = j * n + c;
                    dst[row][col] = src[col][row];
                    dst[row+1][col] = src[col][row+1];
                }

    r = i * n;
    // right elements left
    for (i = 0; i < r; i++)
        for (j = r; j < dim; j++)
            dst[j][i] = src[i][j];
    // buttom elements left
    for (i = r; i < dim; i++)
        for (j = 0; j < dim; j++)
            dst[j][i] = src[i][j];  

    gettimeofday(&end, NULL);
    printf(
        "opt2_transpose:\t%ld.%06ld(block %d)\n",
        end.tv_sec-start.tv_sec,
        labs(end.tv_usec-start.tv_usec),
        n
    );
}
