
// B.
#define R 7
#define S 5
#define T 13

long A[R][S][T];

long store_ele(long i, long j, long k, long *dest)
{
    *dest = A[i][j][k];
    return sizeof(A);
}

// A.
// type_t A[R][S][T]
// &A[i][j][k] = A + sizeof(type_t) * (k + j*T + i*S*T)

// %rax = 3j
// %rax = j + 4 * 3j
// %rsi(j) = i
// %rsi = i * 64
// %rdi(i) = 64i + i
// %rdi = 65i + (j + 4 * 3j) 
// %rdx = 65i + (j + 4 * 3j) + k
// %rax = (&A +)8 * %rdx
// (%rcx) = %rax
// return 3640
