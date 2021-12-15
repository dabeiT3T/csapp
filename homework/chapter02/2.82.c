
// A. if x = -INT_MAX, then -x = -INT_MAX => false
// B. obey the int arith => true
// C. 
// D. 
// E. if x = -1, then x >> 2, x = -4 <= -1 

#include <stdio.h>
#include <inttypes.h>
#include <limits.h>

int main()
{
    /*
    int8_t a = -128;
    int8_t b = -a;
    int32_t c = INT_MIN;
    int32_t d = -INT_MIN;

    printf("%" PRId8 " %" PRId8 "\n", a, b);
    printf("%" PRId32 " %" PRId32 "\n", c, d);
    */

    uint8_t x = -255;
    printf("%" PRIu8 "\n", x);
    printf("%x\n", -255);


    return 0;
}

