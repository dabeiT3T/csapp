#include <stdio.h>

unsigned srl(unsigned x, int k);
int sra(int x, int k);

int main()
{

    unsigned x = 0xffffffff;
    unsigned xs = srl(x, 0);
    int y = 0x80000000;
    int ys = sra(y, 8);

    printf("0x%.8x %u %u\n", xs, x, xs);
    printf("0x%.8x %d %d\n", ys, y, ys);
    return 0;
}

unsigned srl(unsigned x, int k)
{
    unsigned xsra = (int) x >> k;

    int bits = sizeof(int) << 3;
    int umask = (1 << (bits - k - 1) << 1) - 1;
    return xsra & umask;
}

int sra(int x, int k)
{
    int xsrl = (unsigned) x >> k;

    int bits = sizeof(int) << 3;
    int flg_mask = 1 << (bits - k -1);
    int flag = xsrl & flg_mask;
    int umask = ~((flag << 1) - 1);

    return xsrl | umask;
}

