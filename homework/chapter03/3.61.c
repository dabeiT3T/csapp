
// gcc -O1
long cread_alt(long *xp)
{
    long a = 0;
    long *ap = &a;
    if (!xp)
        xp = ap;
    return *xp;
}

