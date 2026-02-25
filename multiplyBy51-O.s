	.file	"multiplyBy51.cpp"
	.text
	.globl	_Z12multiplyBy51P8IntArray
	.type	_Z12multiplyBy51P8IntArray, @function
_Z12multiplyBy51P8IntArray:
.LFB0:
	.cfi_startproc
	endbr64
	cmpl	$0, (%rdi)
	jle	.L1
	movl	$0, %r9d
	movl	$0, %r11d
	jmp	.L5
.L8:
	movl	%eax, (%r10)
	addq	$1, %r9
	cmpl	%r9d, (%rdi)
	jle	.L1
.L5:
	movq	8(%rdi), %rax
	leaq	(%rax,%r9,4), %r10
	movl	(%r10), %esi
	movl	$6, %ecx
	movl	$61, %edx
	movl	%r11d, %eax
.L4:
	leal	(%rax,%rsi), %r8d
	testb	$1, %dl
	cmovne	%r8d, %eax
	addl	%esi, %esi
	sarl	%edx
	subl	$1, %ecx
	jne	.L4
	jmp	.L8
.L1:
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
