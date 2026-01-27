#include <iostream>
#include "Lab3_AlbaPamintuanSinjian_code.h"
using namespace std;

int main(){

    // creating IntNode object i, setting values
    IntNode *i = new IntNode(0, NULL);
    IntNode *j = new IntNode(1, NULL);
    i->linkage = j;

    cout << "The nodeData of i is " << i->nodeData << endl;
    cout << "The nodeData of j is " << i->linkage->nodeData << endl;

    IntList list;
    IntNode *dude = list.initializeHead(5);
    cout << "The head nodeData is " << dude->nodeData << endl;
    cout << "The head nodeData is " << list.returnHead()->nodeData << endl;

    IntNode *head = list.returnHead();
    list.deleteNode(head);

    cout << head->nodeData << endl;

    // deallocate memory
    delete i;
    i = NULL;
    delete j;
    j = NULL;

    return 0;
}
