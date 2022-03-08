    .pos 0
    irmovq stack, %rsp
    call main
    halt

    .align 8
array.0:
    .quad 0xaaa
    .quad 0xddd
    .quad 0xbbb
    .quad 0xccc
    .quad 0xddd
    .quad 0xbbb

array.1:
    .quad .L10          # 0
    .quad .L13          # 1 default
    .quad .L11          # 2
    .quad .L12          # 3
    .quad .L13          # 4 default
    .quad .L11          # 5 2
    .quad .L13          # default

main:
    # ...
    ret

# idx in %rdi
offset:
    xorq %rax, %rax     # result = 0
    irmovq $8, %r8
    irmovq $1, %r9
    jmp .L1

.L2:
    addq %r8, %rax      # result += 8
    subq %r9, %rdi      # idx--
.L1:
    andq %rdi, %rdi     # idx != 0
    jne .L2
    ret 

# idx in %rdi
switchv.0:
    irmovq $5, %r8      # %r8 = 5
    xorq %r9, %r9       # %r9 = 0
    rrmovq %rdi, %rsi   # copy idx
    subq %r8, %rsi      # idx - 5
    irmovq $0xddd, %rax
    jg .L2
    subq %r9, %rdi      # idx - 0
    jl .L2              # no ja here
    call offset         # calculate offset
    irmovq array.0, %rsi
    addq %rsi, %rax
    mrmovq (%rax), %rax
.L0:
    ret

# idx in %rdi
switchv.1:
    irmovq $5, %r8
    xorq %r9, %r9
    irmovq $6, %r10
    rrmovq %rdi, %rsi
    subq %r8, %rsi
    cmovg %r10, %rdi    # %rdi = idx > 5 ? 6 : idx
    subq %r9, %rdi
    cmovl %r10, %rdi    # %rdi = idx < 0 ? 6 : idx
    call offset
    irmovq array.1, %rsi
    addq %rsi, %rax
    pushq %rax
    ret                 # jmp %rax

.L10:
    irmovq $0xaaa, %rax
    ret
.L11:
    irmovq $0xbbb, %rax
    ret
.L12:
    irmovq $0xccc, %rax
    ret
.L13:
    irmovq $0xddd, %rax
    ret

    .pos 0x200
stack:

