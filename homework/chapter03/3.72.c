#include <alloca.h>

long aframe(long n, long idx, long *q)
{
    long i;
    long **p = alloca(n * sizeof(long *));
    p[0] = &i;
    for (i = 1; i < n; i++)
        p[i] = q;
    return *p[idx];
}

// A. s2 = s1 - ((8i+30) & ~15)
// B. p = (s2 + 15) & ~15
// C. max(e1) = 24 when n = 2k+1 (k>=0) and s1 % 16 == 0
//    min(e1) = 16 when n = 2k (k>0) and s1 % 16 == 1
// D. p aligned to 16 bytes
//    s2 aligned to 8 bytes generally
//    by default, stack boundary is 16 bytes, and turned to 8 bytes with a pushq.
//
// explain C:
// alloca (8i+30) & ~16 that is
// bits w3 w2 w1 w0
// 30   1  1  1  0
// 8i   x  0  0  0
// `& ~16` means we lose w0~w3
// if 8i's w3 = 1 => we lose 0b0110 (8i+30-6 get more)
// if 8i's w3 = 0 => we lose 0b1110 (8i+30-14 get less)
// |----------------
// p = (s1 + %rax + 15) & ~16
// bits w3 w2 w1 w0
// s1   x  x  x  x
// %rax 0  0  0  0
// 15   1  1  1  1
// if s1 = 0b0000 then p = 0b1111 & ~16 = 0b0000 which means p is at the top of the stack
// if s1 = 0b0001 then p = 0b10000 & ~16 = 0b10000 which means it wastes 16 - 1 = 15 bytes
// |---------------
// e1 to be max, get more from alloca(-6) and p at the top of the stack
// e1 to be min, get less from alloca(-14) and p wastes more

