#include "IntArray.h"

void multiplyByX(IntArray *p, int x){
    for (int i = 0; i < p->size; i++) {
        p->elements[i] = p->elements[i] * x;
    }

    // Note
    // This code is not checked for edge cases just for simplicity
    // in reading the assembly code.
}
