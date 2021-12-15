#include <stdio.h>

int tsub_ok(int x, int y);

int main()
{
    int a = 1 << 31;
    int b = 1 << 10;

    printf("%d\n", tsub_ok(a, b));

    return 0;
}

int tsub_ok(int x, int y)
{
    int move = (sizeof(int) << 3) - 1;

    int m_x = x >> move;
    int m_y = (~y + 1) >> move;
    int m_s = (x + ~y + 1) >> move;

    return m_x != m_y || m_x == m_s;
}

