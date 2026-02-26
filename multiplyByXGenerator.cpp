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
    cout << "   cmpl	$0, (%rdi)" << endl;
    cout << "   jle	.L1" << endl;
    cout << "   movl	$0, %eax" << endl;
    cout << ".L3:" << endl;
    cout << "   movq	8(%rdi), %rdx" << endl;
    cout << "	leaq	(%rdx,%rax,4), %rdx" << endl;
    
    // Where the 'imull' would be, we have replaced with our function
    // Implementation of Russian Peasant algirorithm (shift-add multiplication)\
    // r8d holds the multiplicand, and r9d holds the multiplier,...
    // ...ecx holds the product
    cout << "	movl 	(%rdx), %r8d" << endl;
    cout << "	movl 	$" << x << ", %r9d" << endl;
    cout << "	movl	$0, %ecx" << endl;
    // Main 'loop', where multiplicand is doubled...
    // and multiplier is halved (rounded down)
    // for halving, we used sarl (shift arithmetic right)
    cout << ".LOOP:" << endl;
    // if r9d is 0, we end the loop
    cout << "	testl	%r9d, %r9d" << endl;
    cout << "	jz .ENDLOOP" << endl;
    // if r9d is even, we skip adding to ecx
    cout << "	testl	$1, %r9d" << endl;
    cout << "	jz .SKIP" << endl;
    cout << "	addl 	%r8d, %ecx" << endl;
    cout << ".SKIP:" << endl;
    // we double r8d and halve r9d
    cout << "	addl 	%r8d, %r8d" << endl;
    cout << "	sarl	$1, %r9d" << endl;
    cout << "	jmp .LOOP" << endl;
    // end of loop
    cout << ".ENDLOOP:" << endl;
    cout << "	movl	%ecx, (%rdx)" << endl;
    cout << "   addq	$1, %rax" << endl;
    cout << "   cmpl	%eax, (%rdi)" << endl;
    cout << "	jg	.L3" << endl;
    cout << ".L1:" << endl;
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
