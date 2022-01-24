
// gcc -O1 -S 3.65.c

// C.
#define M 15

void transpose(long A[M][M])
{
    long i, j;
    for (i = 0; i < M; i++)
        for (j = 0; j < i; j++) {
            long t = A[i][j];
            A[i][j] = A[j][i];
            A[j][i] = t;
        }
}

// A. %rdx A[i][j] move from left to right
// B. %rax A[j][i] move from top to bottom

// %rcx = (%rdx)
// %rsi = (%rax)
// (%rdx) = %rsi
// (%rax) = %rcx
// %rdx += 8
// %rax += 120
// %rax - %rdi != 0
