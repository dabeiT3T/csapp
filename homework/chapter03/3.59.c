#include <inttypes.h>

typedef __int128 int128_t;

void store_prod(int128_t *dest, int64_t x, int64_t y)
{
    *dest = x * (int128_t) y;
}

// define 128bits signed x = 2^64 * signed_high_64bits_x + unsigned_low_64bits_x
// unsigned_low_64bits_x < 2^64
//
// x = 2^64 * s_h_x * u_l_x
// y = 2^64 * s_h_y * u_l_y
//
// x*y = 2^128 * s_h_x * s_h_y + 2^64 * s_h_x * u_l_y + 2^64 * s_h_y * u_l_x + u_l_x * u_l_y
// 2^128 * s_h_x * s_h_y will not affect the lower 128 bits, ignore
//
// x*y = p = 2^64 * s_h_p + u_l_p = 2^64(s_h_x * u_l_y + s_h_y * u_l_x) + u_l_x * u_l_y
// s_h_p = s_h_x * u_l_y + s_h_y * u_l_x + u_l_x * u_l_y / 2^64 - u_l_p / 2^64
// u_l_p < 2^64
// s_h_p = s_h_x * u_l_y + s_h_y * u_l_x + (u_l_x * u_l_y >> 64)
// u_l_p = (u_l_x * u_l_y) mod 2^64
//
// 2. %rax = s_l_y
// 3. %rdx = s_h_y
// 4. %rcx = s_l_x
// 5. %rcx = s_h_x
// 6. %rcx = s_h_x * s_l_y = s_h_x * u_l_y
// 7. %rdx = s_h_y * s_l_x = s_h_y * u_l_x
// 8. $rcx = s_h_x * u_l_y + s_h_y * u_l_x
// 9. $rax = (u_l_x * u_l_y) mod 2^64 = u_l_p, %rdx = u_l_x * u_l_y >> 64
//    (mulq is the unsigned multiplication)
// 10. $rdx = s_h_x * u_l_y + s_h_y * u_l_x + (u_l_x * u_l_y >> 64) = s_h_p
// 11. low_64bits_dest = %rax = u_l_p
// 12. high_64bits_dest = %rdx = s_h_p

