	.file	"multiplyBy61.cpp"
	.text
	.globl	_Z12multiplyBy61P8IntArray
	.type	_Z12multiplyBy61P8IntArray, @function
_Z12multiplyBy61P8IntArray:
.LFB0:
	.cfi_startproc
	endbr64
	cmpl	$0, (%rdi)
	jle	.L1
	movl	$0, %eax
.L3:
	movq	8(%rdi), %rdx
	leaq	(%rdx,%rax,4), %rdx
	# instead of imul, russian peasant algorithm!
	# imull	$61, (%rdx), %ecx
	# registers used: r8d, r9d, r10, ecx
	# r8d holds the 'left collumn'
	# r9d holds the 'right collumn'
	# note: (%rdx) holds the value of the int[] element
	# and here, ecx holds the value of the thingy ig
	movl 	(%rdx), %r8d
	movl 	$61, %r9d
	movl	$0, %ecx
.LOOP:
	# check if r9d is 0
	testl	%r9d, %r9d
	jz .ENDLOOP
	# check if r8d is even...
	testl	$1, %r9d
	# ...and if so, skip addition step
	jz .SKIP
	addl 	%r8d, %ecx
.SKIP:
	# multiply r8d by 2, divide r9d by 2
	addl 	%r8d, %r8d
	sarl	$1, %r9d
	jmp .LOOP
.ENDLOOP:
	# imull	$61, (%rdx), %ecx
	movl	%ecx, (%rdx)
	addq	$1, %rax
	cmpl	%eax, (%rdi)
	jg	.L3
.L1:
	ret
	.cfi_endproc
.LFE0:
	.size	_Z12multiplyBy61P8IntArray, .-_Z12multiplyBy61P8IntArray
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
