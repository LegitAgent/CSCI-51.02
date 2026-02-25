#include <iostream>
#include <string>
#include "IntArray.h"
using namespace std;

int main(int argc, char* argv[]) {
    if(argc != 2) {
        cout << "Usage: ./multiplyByX.out <Number>" << endl;
        return 1;
    }
    int x = stoi(argv[1]);
    if(x <= 0) {
        cout << "Parameter must be a positive constant." << endl;
        return 1;
    }

    string functionName = "multiplyBy" + to_string(x);
    int length = functionName.length();

    string zName = "_Z" + to_string(length) + functionName + "P8IntArray";

    cout << "   .file   \"multiplyBy" << x << ".cpp\"" << endl;
    cout << "   .text" << endl;
    cout << "   .globl " <<  zName << endl;
    cout << "   .type "<< zName << ", @function" << endl;

    cout << zName << ":" << endl;

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
    cout << "   .size   " << zName << ", .-" << zName << endl;
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
    return 0;
}