#include "show_bytes.h"

void show_short();
void show_long();
void show_double();

int main()
{
    show_short();
    show_long();
    show_double();
}

void show_short()
{
    short s = 127;
    show_bytes((byte_pointer) &s, sizeof(s));
}

void show_long()
{
    long l = 0x1122334455;
    show_bytes((byte_pointer) &l, sizeof(l));
}

void show_double()
{
    double d = 0.5;
    show_bytes((byte_pointer) &d, sizeof(d));
}

