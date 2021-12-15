#include <stdio.h>

int int_shifts_are_arithmetic();

int main()
{
    printf("%d\n", int_shifts_are_arithmetic());

    return 0;
}

int int_shifts_are_arithmetic()
{
    int x = -1;

    int bytes = sizeof(int) << 3;

    return (x >> bytes) & 1;
}

int int_shifts_are_arithmetic_answer()
{
    int x = -1;
    return (x >> 1) == -1;
}
