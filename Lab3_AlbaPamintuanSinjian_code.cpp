#include <iostream>
#include "Lab3_AlbaPamintuanSinjian_code.h"
using namespace std;

int main(){

    // creating IntNode object i, setting values
    // IntNode *i = new IntNode(0, NULL);
    // IntNode *j = new IntNode(1, NULL);
    // i->linkage = j;

    // cout << "The nodeData of i is " << i->nodeData << endl;
    // cout << "The nodeData of j is " << i->linkage->nodeData << endl;

    IntList list;
    IntNode *dude = list.initializeHead(5);
    cout << "The head nodeData is " << dude->nodeData << endl;
    cout << "The head nodeData is " << list.returnHead()->nodeData << endl;

    IntNode *arf = list.insertNode(dude, 10);
    cout << "The second nodeData is " << arf->nodeData << endl;

    IntNode *bark = list.insertNode(dude, 15);
    cout << "The now-second nodeData is " << bark->nodeData << endl;
    cout << "The now-third nodeData is " << bark->linkage->nodeData << endl;

    IntNode *head = list.returnHead();
    IntNode *tail = list.returnTail();
    cout << tail->nodeData << endl;

    IntNode *nextNode = list.returnNextNode(head);
    cout << nextNode->nodeData << endl;

    list.deleteNode(tail);
    cout << tail->nodeData << endl;
    list.deleteNode(head);
    cout << head->nodeData << endl;

    cout << "" << endl;

    // Pointer implementation of IntList
    IntList *list2 = new IntList;
    IntNode *head2 = list2->returnHead();

    IntNode *x = list2->initializeHead(5);
    IntNode *y = list2->insertNode(x, 300);
    IntNode *z = list2->insertNode(y, 500);
    IntNode *w = list2->insertNode(x, 30);

    IntNode *foo = new IntNode;
    foo->nodeData = 100;
    foo->linkage = NULL;
    IntNode *nah = list2->insertNode(foo, 0);

    IntNode *first = list2->returnHead();

    // Console output all nodes
    while(first != NULL){
        cout << first->nodeData << endl;
        first = first->linkage;
    }

    cout << "" << endl;
    cout << list2->returnHead()->nodeData << endl;
    list2->deleteNode(x);
    cout << list2->returnHead()->nodeData << endl;

    Stack* stk = new Stack;
    stk->push(23);
    int size = stk->getSize();
    int peek = stk->getPeek();
    stk->pop();
    stk->getPeek();
    cout << size << endl;
    cout << peek << endl;


    // Deallocation memory: list and stack pointers
    delete list2;
    list2 = NULL;

    delete stk;
    stk = NULL;

    // Deallocate memory
    // delete i;
    // i = NULL;
    // delete j;
    // j = NULL;

    return 0;
}
