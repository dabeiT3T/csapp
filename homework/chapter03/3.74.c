#include <stdio.h>
#include <limits.h>

typedef enum {NEG, ZERO, POS, OTHER} range_t;
typedef union {
    unsigned int i;
    float f;
} range;

range_t find_range(float x);
void test();

int main()
{
    test();
    return 0;
}

range_t find_range(float x)
{
    __asm__(
        "movl $0, %eax\n\t"                 // %rax = 0
        "vxorps %xmm1, %xmm1, %xmm1\n\t"    // %xmm1 = 0.0
        "vucomiss %xmm0, %xmm1\n\t"         // 0.0 <=>? x
        "ja .D0\n\t"                        // if 0.0 - x > 0.0 goto .D0
        "setne %sil\n\t"                    // %sil = !ZF
        "movl $3, %edi\n\t"                 // %edi = 3
        "movl $1, %eax\n\t"                 // %eax = 1
        "cmovp %edi, %eax\n\t"              // %eax = PF ? %edi : %eax
        "movzbl %sil, %esi\n\t"             // int %esi = (int) %sil
        "addl %esi, %eax\n\t"               // %eax += %esi
        ".D0:"
    );
}

void test()
{
    int res;
    range r;
    for (r.i = 0; r.i < UINT_MAX; r.i++) {
        res = find_range(r.f);
        if (r.i == 0 || r.i == 0x80000000) {
            if (res != ZERO)
                printf("range ZERO errors when i is %u\n", r.i);
        } else if (r.i <= 0x7f800000) {
            if (res != POS)
                printf("range POS errors when i is %u\n", r.i);
        } else if (r.i > 0x80000000 && r.i <= 0xff800000) {
            if (res != NEG)
                printf("range NEG errors when i is %u\n", r.i);
        } else if (res != OTHER)
            printf("range OTHER errors when i is %u\n", r.i);
    }

    printf("finding range finished.\n");
}

