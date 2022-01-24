	.file	"3.73.c"
	.text
	.globl	find_range
	.type	find_range, @function
find_range:
.LFB12:
	.cfi_startproc
#APP
# 21 "3.73.c" 1
	movl $0, %eax
	vxorps %xmm1, %xmm1, %xmm1
	vucomiss %xmm0, %xmm1
	ja .D0
	setne %sil
	setp %dil
	testb %dil, %dil
	movl $3, %eax
	jne .D0
	movl $1, %eax
	movzbl %sil, %esi
	addl %esi, %eax
	.D0:
# 0 "" 2
#NO_APP
	ret
	.cfi_endproc
.LFE12:
	.size	find_range, .-find_range
	.section	.rodata.str1.8,"aMS",@progbits,1
	.align 8
.LC0:
	.string	"range ZERO errors when i is %u\n"
	.align 8
.LC1:
	.string	"range POS errors when i is %u\n"
	.align 8
.LC2:
	.string	"range NEG errors when i is %u\n"
	.align 8
.LC3:
	.string	"range OTHER errors when i is %u\n"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC4:
	.string	"finding range finished."
	.text
	.globl	test
	.type	test, @function
test:
.LFB13:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	pushq	%rbx
	.cfi_def_cfa_offset 24
	.cfi_offset 3, -24
	subq	$24, %rsp
	.cfi_def_cfa_offset 48
	movl	$0, %ebx
	jmp	.L3
.L8:
	movl	%ebx, 12(%rsp)
	vmovss	12(%rsp), %xmm0
	call	find_range
	testl	%ebx, %ebx
	sete	%cl
	cmpl	$-2147483648, %ebx
	sete	%dl
	orb	%dl, %cl
	je	.L4
	cmpl	$1, %eax
	je	.L5
	movl	%ebp, %esi
	movl	$.LC0, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L4:
	cmpl	$2139095040, %ebp
	ja	.L6
	cmpl	$2, %eax
	.p2align 4,,2
	je	.L5
	movl	%ebp, %esi
	movl	$.LC1, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L6:
	leal	2147483647(%rbp), %edx
	cmpl	$2139095039, %edx
	ja	.L7
	testl	%eax, %eax
	je	.L5
	movl	%ebp, %esi
	movl	$.LC2, %edi
	movl	$0, %eax
	call	printf
	jmp	.L5
.L7:
	cmpl	$3, %eax
	je	.L5
	movl	%ebp, %esi
	movl	$.LC3, %edi
	movl	$0, %eax
	call	printf
.L5:
	leal	1(%rbp), %ebx
.L3:
	movl	%ebx, %ebp
	cmpl	$-1, %ebx
	jne	.L8
	movl	$.LC4, %edi
	call	puts
	addq	$24, %rsp
	.cfi_def_cfa_offset 24
	popq	%rbx
	.cfi_def_cfa_offset 16
	popq	%rbp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE13:
	.size	test, .-test
	.globl	main
	.type	main, @function
main:
.LFB11:
	.cfi_startproc
	subq	$8, %rsp
	.cfi_def_cfa_offset 16
	movl	$0, %eax
	call	test
	movl	$0, %eax
	addq	$8, %rsp
	.cfi_def_cfa_offset 8
	ret
	.cfi_endproc
.LFE11:
	.size	main, .-main
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
