
// A. %rdi = x, %esi = n, %rax = result, %rdx = mask
// B. result = 0; mask = 1;
// C. mask != 0
// D. mask << n
// E. result |= x & mask;
// F.
long loop(long x, int n)
{
    long result = 0;
    long mask;
    for (mask = 1; mask != 0; mask = mask << n) {
        result |= x & mask;
    }
    return result;
}

