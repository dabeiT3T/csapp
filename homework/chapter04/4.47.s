	.file	"4.47.c"
	.text
	.globl	bubble
	.type	bubble, @function
bubble:
.LFB12:
	.cfi_startproc
	leaq	-8(%rdi,%rsi,8), %rsi
	jmp	.L2
.L4:
	movq	8(%rax), %rdx
	movq	(%rax), %rcx
	cmpq	%rcx, %rdx
	jge	.L3
	movq	%rcx, 8(%rax)
	movq	%rdx, (%rax)
.L3:
	addq	$8, %rax
	jmp	.L5
.L6:
	movq	%rdi, %rax
.L5:
	cmpq	%rsi, %rax
	jne	.L4
	subq	$8, %rsi
.L2:
	cmpq	%rdi, %rsi
	jne	.L6
	rep ret
	.cfi_endproc
.LFE12:
	.size	bubble, .-bubble
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%ld "
	.text
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	pushq	%rbx
	.cfi_def_cfa_offset 16
	.cfi_offset 3, -16
	subq	$80, %rsp
	.cfi_def_cfa_offset 96
	movq	$10, (%rsp)
	movq	$9, 8(%rsp)
	movq	$8, 16(%rsp)
	movq	$7, 24(%rsp)
	movq	$6, 32(%rsp)
	movq	$5, 40(%rsp)
	movq	$4, 48(%rsp)
	movq	$3, 56(%rsp)
	movq	$2, 64(%rsp)
	movq	$1, 72(%rsp)
	movl	$10, %esi
	movq	%rsp, %rdi
	call	bubble
	movl	$0, %ebx
	jmp	.L8
.L9:
	movslq	%ebx, %rax
	movq	(%rsp,%rax,8), %rsi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	addl	$1, %ebx
.L8:
	cmpl	$9, %ebx
	jle	.L9
	movl	$10, %edi
	call	putchar
	movl	$0, %eax
	addq	$80, %rsp
	.cfi_def_cfa_offset 16
	popq	%rbx
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
