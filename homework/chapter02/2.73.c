#include <stdio.h>

int saturating_add(int x, int y);

int main()
{
    int a = 0x7fffffff;
    int b = 0xff;

    printf("%d\n", saturating_add(a, b));

    return 0;
}

int saturating_add(int x, int y)
{
    int move = (sizeof(int) << 3) - 1;
    int sum = x + y;

    int m_x = x >> move;
    int m_y = y >> move;
    int m_s = sum >> move;

    int pos_ovf = ~m_x & ~m_y & m_s;
    int neg_ovf = m_x & m_y & ~m_s;
    int novf = ~(pos_ovf | neg_ovf);

    int Tmin = 1 << move;
    int Tmax = ~Tmin;

    return (neg_ovf & Tmin) | (novf & sum) | (pos_ovf & Tmax);
}

