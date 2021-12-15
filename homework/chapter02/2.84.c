

int float_le(float x, float y)
{
    unsigned ux = f2u(x);
    unsigned uy = f2u(y);

    unsigned sx = ux >> 31;
    unsigned sy = uy >> 31;

    return (!sx && (ux <= uy)) || (sx && (ux >= uy)) || (sx ^ sy && (ux & uy == 0x80000000));
}

