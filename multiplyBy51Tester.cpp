#include <iostream>
#include "IntArray.h"
using namespace std;

extern void multiplyBy51(IntArray *p);

int main(){
    // create int array
    // print stuff
    int array[5] = {1, 2, 3, 4, 5};
    IntArray iarr = IntArray{5, array};
    multiplyBy51(&iarr);

    for (int i = 0; i < iarr.size; i++) {
        cout << iarr.elements[i] << endl;
    }

    return 0;
}

