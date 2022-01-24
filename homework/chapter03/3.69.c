
#define CNT 7

typedef struct {
    long idx;
    long x[4];
} a_struct;

typedef struct {
    int first;
    a_struct a[CNT];
    int last;
} b_struct;

void test(long i, b_struct *bp)
{
    int n = bp->first + bp->last;
    a_struct *ap = &bp->a[i];
    ap->x[ap->idx] = n;
}

// %ecx(n) = *(%rsi + 288) # bp->last
// %ecx += *(%rsi) # bp->first
// %rax = 5i
// %rax = bp + 8 * 5i
// %rdx(ap->idx) = *(%rax + 8)
// %rcx = (long) %ecx
// %rax + 8*%rdx + 16 = %rcx
// ret
