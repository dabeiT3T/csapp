	.file	"3.61.c"
	.text
	.globl	cread_alt
	.type	cread_alt, @function
cread_alt:
.LFB0:
	.cfi_startproc
	movq	$0, -8(%rsp)
	leaq	-8(%rsp), %rax
	testq	%rdi, %rdi
	cmove	%rax, %rdi
	movq	(%rdi), %rax
	ret
	.cfi_endproc
.LFE0:
	.size	cread_alt, .-cread_alt
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
