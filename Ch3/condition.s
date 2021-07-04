	.file	"condition.c"
	.text
	.globl	grt
	.type	grt, @function
grt:
.LFB0:
	.cfi_startproc
	cmpl	%esi, %edi
	setg	%al
	movzbl	%al, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	grt, .-grt
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
