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

    // create head node (first node)
    IntNode* initializeHead(int data) {
        if (this->head == NULL){
            this->head = new IntNode(data, NULL);
        }
        return this->head;
    }

    // insert node after ANY node
    IntNode* insertNode(IntNode* existingNode, int data) {
        IntNode *newNode = new IntNode(data, NULL);     // creates new node
        newNode->linkage = existingNode->linkage;       // points newNode to the next node, else segmentation fault
        existingNode->linkage = newNode;
        return newNode;
    }

    IntNode* returnHead() {
        if (this->head != NULL){
            return this->head;
        }
        return NULL;
    }

    IntNode* returnTail() {
        IntNode *tail = this->head;
        while (tail->linkage != NULL){
            tail = tail->linkage;
        }
        return tail;
    }

    IntNode* returnNextNode(IntNode* existingNode) {
        if (existingNode != NULL){
            return existingNode->linkage;
        }
        return NULL;
    }

    // deletes node
    void deleteNode(IntNode* head) {
        IntNode *prev = this->head;     
        while (prev->linkage != head){
            prev = prev->linkage;
        }
        prev->linkage = head->linkage;
        delete head;
        head = NULL;
    }
};

struct IntStack{

};
