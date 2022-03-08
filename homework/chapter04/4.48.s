
.L4:
    mrmovq 8(%rax), %rdx
    mrmovq (%rax), %rcx
    rrmovq %rdx, %r9
    subq %rcx, %r9     # *(p+1) - *p

    cmovge %rdx, %r10
    cmovge %rcx, %rdx
    cmovge %r10, %rcx

    rmmovq %rcx, 8(%rax)
    rmmovq %rdx, (%rax)
