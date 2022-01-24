	.file	"3.75.c"
	.text
	.globl	c_imag
	.type	c_imag, @function
c_imag:
.LFB0:
	.cfi_startproc
	vmovapd	%xmm1, %xmm0
	ret
	.cfi_endproc
.LFE0:
	.size	c_imag, .-c_imag
	.globl	c_real
	.type	c_real, @function
c_real:
.LFB1:
	.cfi_startproc
	rep ret
	.cfi_endproc
.LFE1:
	.size	c_real, .-c_real
	.globl	c_sub
	.type	c_sub, @function
c_sub:
.LFB2:
	.cfi_startproc
	vsubsd	%xmm2, %xmm0, %xmm0
	vsubsd	%xmm3, %xmm1, %xmm1
	ret
	.cfi_endproc
.LFE2:
	.size	c_sub, .-c_sub
	.ident	"GCC: (GNU) 4.8.5 20150623 (Red Hat 4.8.5-44)"
	.section	.note.GNU-stack,"",@progbits
