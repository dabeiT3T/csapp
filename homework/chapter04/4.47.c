#include <stdio.h>

#define DATA_COUNT 10

void bubble(long *data, long count);

int main()
{
    int i;
    long data[DATA_COUNT] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

    bubble(data, DATA_COUNT);

    for (i = 0; i < DATA_COUNT; i++)
        printf("%ld ", data[i]);
    printf("\n");

    return 0;
}

// A.
void bubble(long *data, long count)
{
    // assume count > 0
    long *p, *last;
    long t;
    for (last = data + count - 1; last != data; last--) {
        for (p = data; p != last; p++)
            if (*(p+1) < *p) {
                t = *(p+1);
                *(p+1) = *p;
                *p = t;
            }
    }
}

// B.
// # Y86 no imul, using pointer instead
// # void bubble(long *data, long *last)
// # data in %rdi, last in %rsi
// .bubble
//     irmovq $8, %r8
//     jmp .L2
// .L4:
//     mrmovq 8(%rax), %rdx
//     mrmovq (%rax), %rcx
//     rrmovq %rdx, %r9
//     subq %rcx, %r9
//     jge .L3
//     rmmovq %rcx, 8(%rax)
//     rmmovq %rdx, (%rax)
// .L3:
//     addq %r8, %rax
//     jmp .L5
// .L6:
//     rrmovq %rdi, %rax
// .L5:
//     rrmovq %rax, %r9
//     subq %rsi, %r9
//     jne .L4
//     subq %r8, %rsi
// .L2:
//     rrmovq %rsi, %r9
//     subq %rdi, %r9
//     jne .L6
//     ret
