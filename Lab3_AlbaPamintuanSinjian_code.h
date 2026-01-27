#include <iostream>
using namespace std;

struct IntNode{
    // insert code below
    int nodeData;
};


struct IntList{
    // insert code below
    IntNode* initializeHead(int data) {
        IntNode* head = new IntNode;
        head->nodeData = data;
        head->linkage = nullptr;
        return head;
    };

    IntNode* insertNode(IntNode* &head, int data) {
        IntNode* nextNode = new IntNode;
        nextNode->nodeData = data;
        nextNode->linkage = nullptr;

        // TODO: point the current last node to the new node

        return nextNode; // Is this correct?
    };
};
