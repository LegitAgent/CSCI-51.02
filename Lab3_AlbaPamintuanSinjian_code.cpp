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

    IntList *thing = new IntList;
    IntNode *x = thing->initializeHead(5);
    IntNode *y = thing->insertNode(x, 300);
    IntNode *z = thing->insertNode(y, 500);
    IntNode *w = thing->insertNode(x, 30);

    IntNode *first = thing->returnHead();

    while(first != NULL){
        cout << first->nodeData << endl;
        first = first->linkage;
    }

    cout << "" << endl;
    cout << thing->returnHead()->nodeData << endl;
    thing->deleteNode(x);
    cout << thing->returnHead()->nodeData << endl;

    delete thing;
    thing = NULL;

    // Deallocate memory
    delete i;
    i = NULL;
    delete j;
    j = NULL;

    return 0;
}
