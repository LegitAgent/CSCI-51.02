#include <iostream>
using namespace std;

struct IntNode{
    // Data of the IntNode
    int nodeData;           // int
    IntNode *linkage;       // linkage: The next IntNode

    // Constructor method
    IntNode(int nodeData, IntNode* linkage){
        this->nodeData = nodeData;
        this->linkage = linkage;
    }

    // destructor
    ~IntNode(){
        cout << "me dead, my data was: " << nodeData << endl;
    }
};


struct IntList{
    // local variables
    IntNode *head = NULL;

    // Create head node (first node)
    IntNode* initializeHead(int data) {
        if (this->head == NULL){
            this->head = new IntNode(data, NULL);
        }
        return this->head;
    }

    // Insert node after ANY node
    IntNode* insertNode(IntNode* existingNode, int data) {
        IntNode *newNode = new IntNode(data, NULL);     // creates new node
        newNode->linkage = existingNode->linkage;       // points newNode to the next node, else segmentation fault
        existingNode->linkage = newNode;
        return newNode;
    }

    // Returns the head of the list
    IntNode* returnHead() {
        if (this->head != NULL){
            return this->head;
        }
        return NULL;
    }

    // Returns the tail of the list
    IntNode* returnTail() {
        IntNode *tail = this->head;
        while (tail->linkage != NULL){
            tail = tail->linkage;
        }
        return tail;
    }

    // Returns node linked to existingNode
    IntNode* returnNextNode(IntNode* existingNode) {
        if (existingNode != NULL){
            return existingNode->linkage;
        }
        return NULL;
    }

    // deletes node
    void deleteNode(IntNode* head) {
        if (head = this->head){
            this->head = this->head->linkage;
        }else{
            IntNode *prev = this->head;
            while (prev->linkage != head){
                prev = prev->linkage;
            }
            prev->linkage = head->linkage;
        }
        delete head;
        head = NULL;
    }

    // deletes node AND all children nodes
    void deleteAllNextNodes(IntNode* head){
        IntNode *next = head->linkage;          // Create pointer
        deleteAllNextNodes(next);               // Recursive function call to delete all next nodes
        delete head;                            // Deallocate memory
        head = NULL;                            // Set pointer to null
    }

    // destructor method
    ~IntList(){
        deleteAllNextNodes(this->head);         // Deletes all nodes in the list
                                                // Ensures that if list is deleted, so are all nodes
    }

};

struct IntStack{

};
