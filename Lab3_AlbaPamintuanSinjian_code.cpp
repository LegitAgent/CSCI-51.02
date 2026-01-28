#include <iostream>
#include "Lab3_AlbaPamintuanSinjian_code.h"
using namespace std;

int main(){

    // Creation of IntList object
    IntList list;
    IntNode *dude = list.initializeHead(5);

    // Finding finding head's data
    cout << "The head nodeData is " << dude->nodeData << endl;
    cout << "The head nodeData is " << list.returnHead()->nodeData << endl;

    // Inserting a node into the list
    IntNode *arf = list.insertNode(dude, 10);
    cout << "The second nodeData is " << arf->nodeData << endl;

    // Inserting a node between dude and arf
    IntNode *bark = list.insertNode(dude, 15);
    cout << "The now-second nodeData is " << bark->nodeData << endl;
    cout << "The now-third nodeData is " << bark->linkage->nodeData << endl;

    // Returning head and tail of list
    IntNode *head = list.returnHead();
    IntNode *tail = list.returnTail();
    cout << tail->nodeData << endl;

    // Demonstrating next node method
    IntNode *nextNode = list.returnNextNode(head);
    cout << nextNode->nodeData << endl;

    // Demonstrating deleteNode method
    list.deleteNode(tail);
    cout << tail->nodeData << endl;
    list.deleteNode(head);
    cout << head->nodeData << endl;

    cout << "" << endl;                         // line space to separate, for output readability

    // Pointer implementation of IntList
    IntList *list2 = new IntList;
    // Error: getting head of an empty list
    IntNode *head2 = list2->returnHead();       // should print an error message

    // Filling list with many nodes
    IntNode *x = list2->initializeHead(5);
    IntNode *y = list2->insertNode(x, 300);
    IntNode *z = list2->insertNode(y, 500);
    // Demonstration of adding node between two nodes in list
    IntNode *w = list2->insertNode(x, 30);

    // Error: inserting into a node that isn't in the list
    IntNode *foo = new IntNode;
    foo->nodeData = 100;
    foo->linkage = NULL;
    IntNode *nah = list2->insertNode(foo, 0);   // should print an error message

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


    // Deallocation memory: IntList, IntStack, and IntNode pointers allocated with 'new' keyword
    delete list2;
    list2 = NULL;

    delete stk;
    stk = NULL;

    delete foo;
    foo = NULL;

    // Deallocate memory
    // delete i;
    // i = NULL;
    // delete j;
    // j = NULL;

    return 0;
}
