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
    cout << "LIST DEMONSTRATION (with errors)" << endl;

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

    // Demonstration: delete head, then output data of new head
    cout << list2->returnHead()->nodeData << endl;      // old head
    list2->deleteNode(x);                               // Delete old head
    cout << list2->returnHead()->nodeData << endl;      // output new head

    // Cosmetic title for output readability
    cout << "" << endl;
    cout << "STACK DEMONSTRATION (with errors)" << endl;

    // IntStack Demonstration
    // Creation of stack and populating stack
    IntStack* stk = new IntStack;         // Create pointer to new stack object
    stk->push(23);                  // Push IntNode object with data '23'
    int size = stk->getSize();      // int size variable to hold current size of stack
    int peek = stk->getPeek();      // int peek variable to hold data of current peek
    stk->pop();                     // Pop the stack

    // Error: peeking at empty stack
    stk->getPeek();         // should return Error statement

    // Output size and peek of stack (before pop)
    cout << size << endl;
    cout << peek << endl;


    // Deallocation memory: IntList, IntStack, and IntNode pointers allocated with 'new' keyword
    delete list2;
    list2 = NULL;

    delete stk;
    stk = NULL;

    delete foo;
    foo = NULL;

    return 0;
}
