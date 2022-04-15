#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define MEM_LENGTH 3

void *basic_memset(void *s, int c, size_t n);

int main()
{
    int i;
    void *s;
    unsigned char *schar;

    s = (void *)malloc(MEM_LENGTH);
    if (!s)
        return -1;

    schar = (unsigned char *) basic_memset(s, 0xff, MEM_LENGTH);

    for (i = 0; i < MEM_LENGTH; i++)
        printf("%2d. 0x%x\n", i, *(schar+i));

    schar = NULL;
    free(s);
    return 0;
}

void *basic_memset(void *s, int c, size_t n)
{
    size_t cnt;
    size_t longBytes = sizeof(unsigned long);
    // size_t is unsigned that it must be positive
    size_t limit = n >= longBytes ? n - longBytes + 1 : 0;
    unsigned long longC = 0;
    unsigned char *schar = s;
    unsigned long *slong;
    /** get integer type of address s */
    uintptr_t sptr = (uintptr_t)s;

    for (cnt = 0; cnt < longBytes; cnt++)
        longC |= (unsigned char) c << (cnt << 3);

    // align
    // if longBytes = 8
    // 0b1111 1xxx & (0b111) == 0bxxx
    // if 0bxxx == 0 then sptr % longBytes == 0
    for (cnt = 0; cnt < n && (sptr & (longBytes - 1)); cnt++)
        *schar++ = (unsigned char) c;

    // use longC
    slong = (unsigned long *) schar;
    for (; cnt < limit; cnt += longBytes)
        *slong++ = longC;
    // for i7 has 2 storage units
    // here we may use loop unrolling
    // limit = n - (longBytes << 1) + 1
    // *slong0 = longC;
    // *slong1 = longC;
    // slong0 += 2;
    // slong1 += 2;
    // cnt += longBytes << 1;

    // use low 8-bytes
    schar = (unsigned char *) slong;
    for (; cnt < n; cnt++)
        *schar++ = (unsigned char) c;

    return s;
}
