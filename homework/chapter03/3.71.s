	.file	"3.71.c"
	.text
	.globl	main
	.type	main, @function
main:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	$0, %eax
	call	good_echo
	movl	$0, %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	main, .-main
	.section	.rodata
.LC0:
	.string	"Error opening stdio"
	.text
	.globl	good_echo
	.type	good_echo, @function
good_echo:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$112, %rsp
	movq	stdin(%rip), %rax
	testq	%rax, %rax
	je	.L4
	movq	stdout(%rip), %rax
	testq	%rax, %rax
	jne	.L5
.L4:
	movl	$.LC0, %edi
	call	perror
	movl	$-1, %eax
	jmp	.L10
.L5:
	jmp	.L7
.L9:
	movq	stdout(%rip), %rdx
	leaq	-112(%rbp), %rax
	movq	%rdx, %rsi
	movq	%rax, %rdi
	call	fputs
	leaq	-112(%rbp), %rax
	movq	%rax, %rdi
	call	strlen
	cmpq	$98, %rax
	jbe	.L8
	movzbl	-14(%rbp), %eax
	cmpb	$10, %al
	je	.L8
.L7:
	movq	stdin(%rip), %rdx
	leaq	-112(%rbp), %rax
	movl	$100, %esi
	movq	%rax, %rdi
	call	fgets
	testq	%rax, %rax
	jne	.L9
.L8:
	movl	$0, %eax
.L10:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	good_echo, .-good_echo
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
