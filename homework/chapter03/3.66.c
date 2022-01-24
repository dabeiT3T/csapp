
// gcc -O1 -S 3.66.c

#define NR 3 *
#define NC 1 + 4 *

long sum_col(long n, long A[NR(n)][NC(n)], long j)
{
    long i;
    long result = 0;
    for (i = 0; i < NR(n); i++)
        result += A[i][j];
    return result;
}

// %r8 = 4n + 1
// %rax = 3n
// %rdi(n) = 3n
// %rax <= 0 .L4
// %r8 = 8 * (4n + 1)
// %rcx = A + 8j
// %rax = 0
// %rdx(j) = 0
// .L3
// %rax += *(%rcx)
// %rdx++
// %rcx += %r8
// %rdx - %rdi != 0 .L3
