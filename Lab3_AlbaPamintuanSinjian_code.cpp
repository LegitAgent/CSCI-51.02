#include <iostream>
#include "Lab3_AlbaPamintuanSinjian_code.h"
using namespace std;

int main(){

    // creating IntNode object i, setting values
    IntNode *i = new IntNode();
    i->x = 0;

    cout << i->x << endl;

    // deallocate memory
    delete i;
    i = NULL;

    return 0;
}
