#include "IntArray.h"

void multiplyBy51(IntArray *p){
    for (int i = 0; i < p->size; i++) {
        int x = 0;
        int y = 61;
        int z = p->elements[i];
        while(y != 0){
            if(y & 1 != 0){
                x += z;
            }
            z += z;
            y = y >> 1;
        }
        p->elements[i] = x;
    }

    // Note
    // This code is not checked for edge cases just for simplicity
    // in reading the assembly code.
}
