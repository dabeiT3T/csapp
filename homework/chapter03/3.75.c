#include <complex.h>

double c_imag(double complex x)
{
    return cimag(x);
}

double c_real(double complex x)
{
    return creal(x);
}

double complex c_sub(double complex x, double complex y)
{
    return x - y;
}

// A. %xmm0/%xmm2/%xmm4/%xmm6 => real part
//    %xmm1/%xmm3/%xmm5/%xmm7 => imaginary part
// B. %xmm0 => real part
//    %xmm1 => imaginary part
