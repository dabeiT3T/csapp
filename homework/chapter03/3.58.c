
long decode2(long x, long y, long z)
{
    // y -= z;
    // x *= y;
    // %rax = y;
    // %rax <<= 63;
    // $rax >>= 63;
    // $rax |= x;
    y -= z;
    x *= y;
    y <<= 63;
    y >>= 63;
    return y ^ x;
}

