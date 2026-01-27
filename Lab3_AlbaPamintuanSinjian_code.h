#include <iostream>
using namespace std;

struct IntNode{
    // insert code below
    int nodeData;
    IntNode *linkage;

    // constructor
    IntNode(int nodeData, IntNode* linkage){
        this->nodeData = nodeData;
        this->linkage = linkage;
    }

    // destructor
    ~IntNode(){
        cout << "NOO BRO DIED" << endl;
    }
};


struct IntList{
    // local variables
    IntNode *head = NULL;

    IntNode* initializeHead(int data) {
        if (this->head == NULL){
            this->head = new IntNode(data, NULL);
        }
        return this->head;
    }


    IntNode* insertNode(IntNode* head, int data) {
        IntNode nextnode(data, NULL);
        IntNode *next;
        next = &nextnode;
        // TODO: point the current last node to the new node
        
        if(head != NULL){
        head->linkage = next;
        }

        return next; // Is this correct?
    }


    IntNode* returnHead() {
        return this->head;
    }


    void deleteNode(IntNode* deletus) {
        delete deletus;
        deletus = NULL;
    }
};
