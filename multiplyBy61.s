	.file	"multiplyBy61.cpp"
	.text
	.globl	_Z11multiplyBy61P8IntArray
	.type	_Z11multiplyBy61P8IntArray, @function
_Z11multiplyBy61P8IntArray:
.LFB0:
	.cfi_startproc
	endbr64
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movq	%rdi, -24(%rbp)
	movl	$0, -4(%rbp)
	jmp	.L2
.L3:
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rdx, %rax
	movl	(%rax), %ecx
	movq	-24(%rbp), %rax
	movq	8(%rax), %rax
	movl	-4(%rbp), %edx
	movslq	%edx, %rdx
	salq	$2, %rdx
	addq	%rax, %rdx
    movl    $61, %ebx
    movl    $0, %eax
.LOOP:
    movl    %ebx, %edx
    cmpl    $0, %edx
    je .END
    andl    $1, %edx
    cmpl    $0, %edx
    je .SKIP
    addl    %ecx, %eax
.SKIP:
    sall    $1, %ecx
    sarl    $1, %ebx
    jmp .LOOP
.END:
	movl	%eax, (%rdx)
	addl	$1, -4(%rbp)
.L2:
	movq	-24(%rbp), %rax
	movl	(%rax), %eax
	cmpl	%eax, -4(%rbp)
	jl	.L3
	nop
	nop
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	_Z11multiplyBy61P8IntArray, .-_Z11multiplyBy61P8IntArray
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
