#include <iostream>
#include "Lab3_AlbaPamintuanSinjian_code.h"
using namespace std;

int main(){

    // creating IntNode object i, setting values
    IntNode *i = new IntNode;
    i->nodeData = 0;
    IntNode *j = new IntNode;
    j->nodeData = 1;
    i->linkage = j;

    cout << i->nodeData << endl;
    cout << i->linkage->nodeData << endl;

    IntList list;
    IntNode *dude = list.initializeHead(5);
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
