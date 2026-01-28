#include <iostream>
using namespace std;

struct IntNode{
    // Data of the IntNode
    int nodeData;                                       // int
    IntNode *linkage;                                   // linkage: The next IntNode

    // Constructor method
    IntNode(int nodeData, IntNode* linkage){
        this->nodeData = nodeData;                      // Set node data to int parameter 'nodeData'
        this->linkage = linkage;                        // Set linkage (next node) to a pointer to an IntNode
    }

    // Destructor method
    ~IntNode(){
        cout << "node deleted" << nodeData << endl;     // Console output for demonstration        
    }
};


struct IntList{
    // local variables
    IntNode *head = nullptr;                            // Head is initially a nullptr

    // Create head node (first node)
    IntNode* initializeHead(int data) {
        if (this->head == nullptr){                     // If head is nullptr (empty list): 
            this->head = new IntNode(data, nullptr);    // Set head to a new IntNode with nodeData 'data' with no next IntNode (nullptr)
        }
        return this->head;                              // Return head IntNode pointer
    }

    // Insert node after ANY node
    IntNode* insertNode(IntNode* existingNode, int data) {

        // Edge case check: IntNode passed is null
        if (existingNode == nullptr){                   // If the IntNode being passed is null:
            cout << "error: trying to insert an IntNode after a null IntNode"   // Error message
            return nullptr;                                                     // Return a nullptr
        }
        
        // Edge case check: list is empty (no head)
        if (this->head == nullptr){
            cout << "error: trying to insert in an empty list"                  // Error message
            return nullptr;
        }

        // Edge case check: existingNode is a non-null IntNode, but not in the IntList
        IntNode *head = this->head;                     // Head variable to traverse through list
        while (head != existingNode && head != nullptr){                        // Traverse through list until head is null
            head = head->linkage;                       // Set head to next IntNode
        }
        if (head != existingNode){                      // After the traversal through list, check if head is not the existing node
            cout << "error: IntNode does not exist in the list"                 // Error message: IntNode is not in the list
            return nullptr;                             // return null pointer
        }

        IntNode *newNode = new IntNode(data, nullptr);  // Creates new IntNode
        newNode->linkage = existingNode->linkage;       // Points newNode to the next node, else segmentation fault
        existingNode->linkage = newNode;                // Set existingNode's linkage to the newNode (new node comes after existing node)
        return newNode;                                 // Return the new node;
    }

    // Returns the head of the list
    IntNode* returnHead() {
        // Check if head is not null
        if (this->head != nullptr){
            return this->head;                          // Early return: Return head
        }

        // If list is empty (head is null)
        cout << "error: attempting to return head in an empty list";
        return nullptr;
    }

    // Returns the tail of the list
    IntNode* returnTail() {
        // Check if list is empty (head is not null)
        IntNode *tail = this->head;                     // Tail initially set to head
        if(tail == nullptr){                            // If tail is null:
            cout << "error: attempting to return tail in an empty list";        // Error message: empty list
        }
        // Traverse to the list until the end
        while (tail->linkage != nullptr){               // While the next node is not null:
            tail = tail->linkage;                       // Set tail to the next node
        }
        return tail;                                    // Return tail
    }

    // Returns node linked to existingNode
    IntNode* returnNextNode(IntNode* existingNode) {
        // Check if
        if (existingNode != nullptr){
            return existingNode->linkage;
        }
        return nullptr;
    }

    // Deletes node in list, then relinks previous and next node
    void deleteNode(IntNode* head) {
        // If deleting the head:
        if (head = this->head){
            this->head = this->head->linkage;           // Set head to pointer after the head
        }else{
            
            IntNode *prev = this->head;
            while (prev->linkage != head && prev->linkage != nullptr){
                prev = prev->linkage;
            }

            // Edge case: IntNode passed is not in the list
            if (prev->linkage != head){
                cout << "error: attempting to delete IntNode that is not in the list";
            
            // If IntNode is in list:
            }else{
                prev->linkage = head->linkage;          // Set the linkage of previous node to head's linkage ('relink' list deletion)
                delete head;                            // Delete the node
                head = nullptr;                         // Set the pointer to null
            }
        }
    }

    // deletes node AND all children nodes
    void deleteAllNextNodes(IntNode* head){
        IntNode *next = head->linkage;          // Create pointer pointing to linkage (next node)
        if (next != nullptr){
            deleteAllNextNodes(next);           // Recursive function call to delete all next nodes
        }
        delete head;                            // Deallocate memory
        head = nullptr;                         // Set pointer to null
    }

    // destructor method
    ~IntList(){
        deleteAllNextNodes(this->head);         // Deletes all nodes in the list
                                                // Ensures that if list is deleted, so are all nodes
    }

};

struct Stack {
    IntNode* peek = nullptr;
    int size = 0;
    void push(int _data) {
        IntNode* temp = new IntNode;
        temp->data = _data;
        temp->next = peek;
        peek = temp;
        size++;
        return;
    }
    void pop() {
        if(size == 0) {
            cout << "ERROR: Stack is empty" << endl;
        }
        IntNode* temp = peek;
        peek = peek->next;
        delete temp;
        size--;
    }
    int getSize() {
        return size;
    }
    int getPeek() {
        if(peek == nullptr) {
            cout << "ERROR: Stack is empty" << endl;
            return 0;
        }
        return peek->data;
    }
    ~Stack() {
        while (peek != nullptr) {
            IntNode* temp = peek;
            peek = peek->next;
            delete temp;
        }
    }
};