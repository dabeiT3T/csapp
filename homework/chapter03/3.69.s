	.file	"3.69.c"
	.text
	.globl	test
	.type	test, @function
test:
.LFB0:
	.cfi_startproc
	movl	288(%rsi), %ecx
	addl	(%rsi), %ecx
	leaq	(%rdi,%rdi,4), %rax
	salq	$3, %rax
	addq	%rsi, %rax
	movq	8(%rax), %rdx
	movslq	%ecx, %rcx
	movq	%rcx, 16(%rax,%rdx,8)
	ret
	.cfi_endproc
.LFE0:
	.size	test, .-test
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
