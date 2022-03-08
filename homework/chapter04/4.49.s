
.L4:
    mrmovq 8(%rax), %rdx
    mrmovq (%rax), %rcx

    rrmovq %rdx, %r10
    xorq %rcx, %r10     # %r10 = %rdx ^ %rcx

    rrmovq %rdx, %r9
    subq %rcx, %r9      # *(p+1) - *p

    cmovl %rcx, %rdx

    rmmovq %rdx, 8(%rax)
    xorq %r10, %rdx
    rmmovq %rdx, (%rax)
