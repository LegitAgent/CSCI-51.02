#include <iostream>
using namespace std;

struct IntNode{
    // Data of the IntNode
    int nodeData;                                       // int
    IntNode *linkage;                                   // linkage: The next IntNode
};


struct IntList{
    // local variables
    IntNode *head = NULL;                            // Head is initially a NULL

    // Create head node (first node)
    IntNode* initializeHead(int data) {
        if (this->head == NULL){                     // If head is NULL (empty list): 
            this->head = new IntNode;    // Set head to a new IntNode with nodeData 'data' with no next IntNode (NULL)
            head->nodeData = data;
            head->linkage = NULL;
        }
        return this->head;                              // Return head IntNode pointer
    }

    // Insert node after ANY node
    IntNode* insertNode(IntNode* existingNode, int data) {

        // Edge case check: IntNode passed is null
        if (existingNode == NULL){                   // If the IntNode being passed is null:
            cout << "ERROR: trying to insert an IntNode after a null IntNode";  // Error message
            return NULL;                                                        // Return a NULL
        }
        
        // Edge case check: list is empty (no head)
        if (this->head == NULL){
            cout << "ERROR: trying to insert in an empty list";                 // Error message
            return NULL;
        }

        // Edge case check: existingNode is a non-null IntNode, but not in the IntList
        IntNode *head = this->head;                     // Head variable to traverse through list
        while (head != existingNode && head != NULL){                        // Traverse through list until head is null
            head = head->linkage;                       // Set head to next IntNode
        }
        if (head != existingNode){                      // After the traversal through list, check if head is not the existing node
            cout << "ERROR: IntNode does not exist in the list";                // Error message: IntNode is not in the list
            return NULL;                             // return null pointer
        }

        IntNode *newNode = new IntNode;     // Creates new IntNode
        newNode->nodeData = data;
        newNode->linkage = existingNode->linkage;       // Points newNode to the next node, else segmentation fault
        existingNode->linkage = newNode;                // Set existingNode's linkage to the newNode (new node comes after existing node)
        return newNode;                                 // Return the new node;
    }

    // Returns the head of the list
    IntNode* returnHead() {
        // Check if head is not null
        if (this->head != NULL){
            return this->head;                          // Early return: Return head
        }

        // If list is empty (head is null)
        cout << "ERROR: attempting to return head in an empty list";
        return NULL;
    }

    // Returns the tail of the list
    IntNode* returnTail() {
        // Check if list is empty (head is not null)
        IntNode *tail = this->head;                     // Tail initially set to head
        if(tail == NULL){                               // If tail is null:
            cout << "ERROR: attempting to return tail in an empty list";        // Error message: empty list
        }
        // Traverse to the list until the end
        while (tail->linkage != NULL){                  // While the next node is not null:
            tail = tail->linkage;                       // Set tail to the next node
        }
        return tail;                                    // Return tail
    }

    // Returns node linked to existingNode
    IntNode* returnNextNode(IntNode* existingNode) {
        // Check if
        if (existingNode != NULL){
            return existingNode->linkage;
        }
        return NULL;
    }

    // Deletes node in list, then relinks previous and next node
    void deleteNode(IntNode* head) {
        // If deleting the head:
        if (head = this->head){
            this->head = this->head->linkage;           // Set head to pointer after the head
        }else{
            
            IntNode *prev = this->head;
            while (prev->linkage != head && prev->linkage != NULL){
                prev = prev->linkage;
            }

            // Edge case: IntNode passed is not in the list
            if (prev->linkage != head){
                cout << "ERROR: attempting to delete IntNode that is not in the list";
            
            // If IntNode is in list:
            }else{
                prev->linkage = head->linkage;          // Set the linkage of previous node to head's linkage ('relink' list deletion)
                delete head;                            // Delete the node
                head = NULL;                         // Set the pointer to null
            }
        }
    }

    // deletes node AND all children nodes
    void deleteAllNextNodes(IntNode* head){
        IntNode *next = head->linkage;          // Create pointer pointing to linkage (next node)
        if (next != NULL){
            deleteAllNextNodes(next);           // Recursive function call to delete all next nodes
        }
        delete head;                            // Deallocate memory
        head = NULL;                            // Set pointer to null
    }

    // destructor method
    ~IntList(){
        deleteAllNextNodes(this->head);         // Deletes all nodes in the list
                                                // Ensures that if list is deleted, so are all nodes
    }

};

struct Stack {

    // Variables
    IntNode* peek = NULL;                       // Peek variable (top of the stack)
    int size = 0;                               // Size variable (how many IntNodes in stack)

    // Push: push IntNode variable into the stack
    void push(int _data) {
        IntNode* temp = new IntNode;            // Create temp IntNode variable
        temp->nodeData = _data;                 // Set nodeData to _data
        temp->linkage = peek;                   // Set next node to peek
        peek = temp;                            // Set peek to temp (temp is now at top of the stack)
        size++;                                 // Increment size by 1
        return;
    }

    // Pop: 
    void pop() {

        // Edge case: trying to pop an empty stack
        if(size == 0) {
            cout << "ERROR: attempting to pop an empty stack" << endl;    // Error Message: stack is empty
        }

        IntNode* temp = peek;                   
        peek = peek->linkage;
        delete temp;
        temp = NULL;
        size--;
    }

    // Method to return size (number of nodes in stack)
    int getSize() {
        return size;                            // return size
    }

    // Peek: look at top of the stack
    int getPeek() {
        if(peek == NULL) {
            cout << "ERROR: attempting to peek at an empty stack" << endl;
            return 0;
        }
        return peek->nodeData;
    }


    ~Stack() {
        while (peek != NULL) {
            IntNode* temp = peek;
            peek = peek->linkage;
            delete temp;
        }
    }
};