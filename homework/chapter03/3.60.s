	.file	"3.60.c"
	.text
	.globl	loop
	.type	loop, @function
loop:
.LFB0:
	.cfi_startproc
	movl	%esi, %ecx
	movl	$1, %edx
	movl	$0, %eax
	jmp	.L2
.L3:
	movq	%rdi, %r8
	andq	%rdx, %r8
	orq	%r8, %rax
	salq	%cl, %rdx
.L2:
	testq	%rdx, %rdx
	jne	.L3
	rep ret
	.cfi_endproc
.LFE0:
	.size	loop, .-loop
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
