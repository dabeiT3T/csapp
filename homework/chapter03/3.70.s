	.file	"3.70.c"
	.text
	.globl	proc
	.type	proc, @function
proc:
.LFB0:
	.cfi_startproc
	movq	8(%rdi), %rax
	movq	(%rax), %rdx
	movq	(%rdx), %rdx
	subq	8(%rax), %rdx
	movq	%rdx, (%rdi)
	ret
	.cfi_endproc
.LFE0:
	.size	proc, .-proc
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
