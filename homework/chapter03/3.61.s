	.file	"3.61.c"
	.text
	.p2align 4,,15
	.globl	cread_alt
	.type	cread_alt, @function
cread_alt:
.LFB0:
	.cfi_startproc
	xorl	%eax, %eax
	testq	%rdi, %rdi
	je	.L5
	rep ret
	.p2align 4,,10
	.p2align 3
.L5:
	movq	0, %rax
	ret
	.cfi_endproc
.LFE0:
	.size	cread_alt, .-cread_alt
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
