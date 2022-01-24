
long switch_prob(long x, long n)
{
    long result = x;
    switch(n) {
        case 60:
        case 62:
            result = 8 * x;
            break; 

        case 63:
            // result = x;
            // result >>= 3;
            result = x >> 3;
            break;
        case 64:
            // result = x;
            // result <<= 4;
            // result -= x;
            // x = result;
            x = 15 * x;
        case 65:
            x *= x;

        default:
            result = x + 0x4b;
    }
    return result;
}

