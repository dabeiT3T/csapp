	.file	"3.58.c"
	.text
	.globl	decode2
	.type	decode2, @function
decode2:
.LFB0:
	.cfi_startproc
	subq	%rdx, %rsi
	imulq	%rsi, %rdi
	movq	%rsi, %rax
	salq	$63, %rax
	sarq	$63, %rax
	xorq	%rdi, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	decode2, .-decode2
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
