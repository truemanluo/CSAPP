	.file	"if_else.c"
	.text
	.globl	switch_case
	.type	switch_case, @function
switch_case:
.LFB0:
	.cfi_startproc
	cmpl	$1, %edi
	je	.L5
	cmpl	$2, %edi
	je	.L6
	movl	$0, %eax
	ret
.L5:
	movl	%edi, %eax
	imull	%esi, %eax
	ret
.L6:
	movl	%esi, %eax
	imull	%esi, %eax
	imull	%edi, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	switch_case, .-switch_case
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
