
int bad_int_size_is_32()
{
    int set_msb = 1 << 31;
    /* some machine use << (x % 32) */
    int beyond_msb = 1 << 32;

    return set_msb && !beyond_msb;
}

// B.
int int_size_is_32_al_32()
{
    int set_msb = 1 << 31;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

// C.
int int_size_is_32_al_16()
{
    int set_msb = 1 << 15 << 15 << 1;
    int beyond_msb = set_msb << 1;
    return set_msb && !beyond_msb;
}

// A. left/right shift count should less than the width of type
