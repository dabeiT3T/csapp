	.file	"3.59.c"
	.text
	.globl	store_prod
	.type	store_prod, @function
store_prod:
.LFB4:
	.cfi_startproc
	movq	%rdx, %rax
	cqto
	movq	%rsi, %rcx
	sarq	$63, %rcx
	imulq	%rax, %rcx
	imulq	%rsi, %rdx
	addq	%rdx, %rcx
	mulq	%rsi
	addq	%rcx, %rdx
	movq	%rax, (%rdi)
	movq	%rdx, 8(%rdi)
	ret
	.cfi_endproc
.LFE4:
	.size	store_prod, .-store_prod
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
