// THE HARD PART
// insert code below
#include <iostream>
#include "IntArray.h"
using namespace std;

void multiplyByXGenerator(int x) {

    /* 
    NOTICE
    It might be best that you create a copy of multiplyByX.cpp and rename X to the number you're multiplying.

    You do not need to change the function name.

    Modify line 12 of multiplyByXTester.cpp when compiling with the output of this generator.
    */

    cout << "   .file   \"multiplyBy" << x << ".cpp\"" << endl;
    cout << "   .text" << endl;
    cout << "   .globl  _Z11multiplyByXP8IntArray" << endl;
    cout << "   .type   _Z11multiplyByXP8IntArray, @function" << endl;

    cout << "_Z11multiplyByXP8IntArray:" << endl;

    cout << ".LFB0:" << endl;
    cout << "   .cfi_startproc" << endl;
    cout << "   endbr64" << endl;
    cout << "   pushq	%rbp" << endl;
    cout << "   .cfi_def_cfa_offset 16" << endl;
    cout << "   .cfi_offset 6, -16" << endl;
    cout << "   movq	%rsp, %rbp" << endl;
    cout << "   .cfi_def_cfa_register 6" << endl;
    cout << "   movq	%rdi, -24(%rbp)" << endl;
    cout << "   movl	$0, -4(%rbp)" << endl;
    cout << "   jmp	.L2" << endl;

    cout << ".L3:" << endl;
    cout << "   movq	-24(%rbp), %rax" << endl;
    cout << "	movq	8(%rax), %rax" << endl;
    cout << "	movl	-4(%rbp), %edx" << endl;
    cout << "	movslq	%edx, %rdx" << endl;
    cout << "	salq	$2, %rdx" << endl;
    cout << "	addq	%rdx, %rax" << endl;
    cout << "	movl	(%rax), %ecx" << endl;
    cout << "	movq	-24(%rbp), %rax" << endl;
    cout << "	movq	8(%rax), %rax" << endl;
    cout << "	movl	-4(%rbp), %edx" << endl;
    cout << "	movslq	%edx, %rdx" << endl;
    cout << "	salq	$2, %rdx" << endl;
    cout << "	addq	%rax, %rdx" << endl;
    cout << "	imull   $" << x << ", %ecx, %eax" << endl;
    cout << "	movl	%eax, (%rdx)" << endl;
    cout << "	addl	$1, -4(%rbp)" << endl;

    cout << ".L2:" << endl;
    cout << "	movq	-24(%rbp), %rax" << endl;
    cout << "	movl	(%rax), %eax" << endl;
    cout << "	cmpl	%eax, -4(%rbp)" << endl;
    cout << "	jl	.L3" << endl;
    cout << "	nop" << endl;
    cout << "	nop" << endl;
    cout << "	popq	%rbp" << endl;
    cout << "	.cfi_def_cfa 7, 8" << endl;
    cout << "	ret" << endl;
    cout << "	.cfi_endproc" << endl;

    cout << ".LFE0:" << endl;
    cout << "   .size   _Z11multiplyByXP8IntArray, .-_Z11multiplyByXP8IntArray" << endl;
    cout << "   .ident	\"GCC: (Ubuntu 13.3.0-6ubuntu2~24.04) 13.3.0\"" << endl;
    cout << "   .section	.note.GNU-stack,\"\",@progbits" << endl;
    cout << "	.section	.note.gnu.property,\"a\"" << endl;
    cout << "	.align 8" << endl;
    cout << "	.long	1f - 0f" << endl;
    cout << "	.long	4f - 1f" << endl;
    cout << "	.long	5" << endl;

    cout << "0:" << endl;
    cout << "	.string	\"GNU\"" << endl;

    cout << "1:" << endl;
    cout << "	.align 8" << endl;
    cout << "	.long	0xc0000002" << endl;
    cout << "	.long	3f - 2f" << endl;

    cout << "2:" << endl;
    cout << "	.long	0x3" << endl;

    cout << "3:" << endl;
    cout << "	.align 8" << endl;

    cout << "4:\n" << endl;
}

int main() {
    cout << "Input a factor: ";
    int factor;
    cin >> factor;
    multiplyByXGenerator(factor);

    return 0;
}