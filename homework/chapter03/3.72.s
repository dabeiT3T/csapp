	.file	"3.72.c"
	.text
	.globl	aframe
	.type	aframe, @function
aframe:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$16, %rsp
	leaq	30(,%rdi,8), %rax
	andq	$-16, %rax
	subq	%rax, %rsp
	leaq	15(%rsp), %r8
	andq	$-16, %r8
	movq	%r8, %rcx
	leaq	-8(%rbp), %rax
	movq	%rax, (%r8)
	movq	$1, -8(%rbp)
	jmp	.L2
.L3:
	movq	%rdx, (%rcx,%rax,8)
	addq	$1, %rax
	movq	%rax, -8(%rbp)
.L2:
	movq	-8(%rbp), %rax
	cmpq	%rdi, %rax
	jl	.L3
	movq	(%r8,%rsi,8), %rax
	movq	(%rax), %rax
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	aframe, .-aframe
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
