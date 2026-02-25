	.file	"multiplyBy51.cpp"
	.text
	.globl	_Z12multiplyBy51P8IntArray
	.type	_Z12multiplyBy51P8IntArray, @function
_Z12multiplyBy51P8IntArray:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -16(%rbp)
	jmp	.L2
.L6:
	movl	$0, -12(%rbp)
	movl	$61, -8(%rbp)
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %eax
	movl	%eax, -4(%rbp)
	jmp	.L3
.L5:
	movl	-8(%rbp), %eax
	andl	$1, %eax
	testl	%eax, %eax
	je	.L4
	movl	-4(%rbp), %eax
	addl	%eax, -12(%rbp)
.L4:
	sall	-4(%rbp)
	sarl	-8(%rbp)
.L3:
	cmpl	$0, -8(%rbp)
	jne	.L5
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	-16(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
	movl	-12(%rbp), %eax
	movl	%eax, (%rdx)
	addl	$1, -16(%rbp)
.L2:
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, -16(%rbp)
	jl	.L6
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z12multiplyBy51P8IntArray, .-_Z12multiplyBy51P8IntArray
	.ident	"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0"
	.section	.note.GNU-stack,"",@progbits
	.section	.note.gnu.property,"a"
	.align 8
	.long	1f - 0f
	.long	4f - 1f
	.long	5
0:
	.string	"GNU"
1:
	.align 8
	.long	0xc0000002
	.long	3f - 2f
2:
	.long	0x3
3:
	.align 8
4:
