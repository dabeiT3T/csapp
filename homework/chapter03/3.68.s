	.file	"3.68.c"
	.text
	.globl	setVal
	.type	setVal, @function
setVal:
.LFB0:
	.cfi_startproc
	movslq	8(%rsi), %rax
	addq	32(%rsi), %rax
	movq	%rax, 184(%rdi)
	ret
	.cfi_endproc
.LFE0:
	.size	setVal, .-setVal
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
