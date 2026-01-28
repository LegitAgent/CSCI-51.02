#include <iostream>
using namespace std;

struct IntNode {
    int data;
    IntNode *next;
};

struct IntList {
    IntNode* head = nullptr;                                            // initialize head as a nullptr pointer
    int size = 0;                                                       // initialize size of list to 0
    IntNode* createHead(int _data) {
        if(head == nullptr) {                                           // if the head is a nullptr pointer
            size++;                                                     // increment size since we will create a node in the list
            head = new IntNode;                                         // make a new int node
            head->next = nullptr;                                       // make its next value to be nullptr since it is the head
            head->data = _data;                                         // make its data value to be the data inputed
            return head;
        } else {
            cout << "ERROR: Existing head, already exists" << endl;     // if there already exists a head, then print an error message
            return nullptr;                                             // return a nullptr pointer
        }
    }
    IntNode* insertAfter(IntNode*& prevNode, int _data) {
        if(prevNode == nullptr) {                                       // if the prev node is nullptr
            cout << "ERROR: This node does not exist" << endl;          // then print out an error message
            return nullptr;                                             // return nullptr
        }
        size++;                                                         // increment size since we are creating a new node
        IntNode* newNode = new IntNode;                                 // make a new node
        newNode->data = _data;                                          // make its data value equal to the data inputed
        newNode->next = prevNode->next;                                 // make the new nodes next value to be the previous nodes next value
        prevNode->next = newNode;                                       // the previous node now points to the new node

        return newNode;                                                 // return the new node
    }
    IntNode* getHead() {
        if(head == nullptr) {                                           // if the head is a nullptr pointer
            cout << "ERROR: Head does not exist" << endl;               // print the error message
            return nullptr;
        }
        return head;                                                    // return the head
    }
    IntNode* getAfter(IntNode* prevNode) {
        if(prevNode == nullptr) {                                       // if the node you are getting isn't nullptr
            cout << "ERROR: This node does not exist" << endl;          // print err msg
            return nullptr;
        }
        IntNode* newNode = prevNode->next;                              // get the node after the prev node
        return newNode;                                                 // return that node
    }
    void deleteNode(IntNode*& node) {
        if(node == nullptr || size < 1) {                               // if the node does not exist or the list is empty
            cout << "ERROR: This node does not exist" << endl;          // print error
            return;
        } else if(node == head) {                                       // if the node is the head
            size--;                                                     // decrease size since we are deleting
            head = head->next;                                          // make the head equal to the next address
            delete node;                                                // delete the node
            node = nullptr;                                             // make sure to declare it to be nullptr
            return;
        }
        IntNode* temp = head;                                           // make a temp variable
        for(int i = 0; i < size; i++) {                                 // loop through the list
            if(temp->next != nullptr && temp->next == node) {           // if the next address is nullptr meaning its the end or if the next node is the node we are looking for
                temp->next = node->next;                                // pass it to be the temp
                delete node;                                            // delete it
                node = nullptr;                                         
                size--;                                                 // decrease size
                return;
            }
            temp = temp->next;                                          // move the list
        }
        cout << "ERROR: Node does not exist" << endl;                   // if it doesn't find it, print err msg
        return;
    }
    ~IntList() {
        while (head != nullptr) {                                       // while the list has elements
            IntNode* temp = head;                                       // get the head and store it in a temp var
            head = head->next;                                          // make the head equal to the next element
            delete temp;                                                // delete it
            temp = nullptr;                                            
        }
    }
};

struct IntStack {
    IntNode* peek = nullptr;                                            // declare a peek pointer
    int size = 0;                                                       // declare size to be 0
    void push(int _data) {
        IntNode* temp = new IntNode;                                    // make a new temp node
        temp->data = _data;                                             // make the temp node data to be the data that was inputted
        temp->next = peek;                                              // make the temp node next to be the peek
        peek = temp;                                                    // peek is now the temp since it is the newest push to the stack
        size++;                                                         // increment size
        return;
    }
    int pop() {
        if(size == 0) {                                                 // if the stack is empty
            cout << "ERROR: Stack is empty" << endl;                    // print err msg
            return 0;
        }
        IntNode* temp = peek;                                           // if not, make a temp that is the peek
        int val = peek->data;
        peek = peek->next;                                              // access the element next to the peek
        delete temp;                                                    // delete the temp var
        temp = nullptr;                                                 // delete it
        size--;                                                         // decrement the size
        return val;
    }
    int getSize() {
        return size;                                                    // returns the size of the stack
    }
    int getPeek() {
        if(peek == nullptr) {                                           // if the stack is empty
            cout << "ERROR: Stack is empty" << endl;                    // give err msg
            return 0;
        }
        return peek->data;                                              // return the data of the peek of the stack
    }
    ~IntStack() {                                                       // deconstructor
        while (peek != nullptr) {                                       // while the stack has elements
            IntNode* temp = peek;                                       // get the peek and store to temp
            peek = peek->next;                                          // make peek equal the next node
            delete temp;                                                // delete temp
            temp = nullptr;                                                // delete
        }
    }
};

int main(){
    // sample usage of linkedlist
    IntList* list = new IntList;
    IntNode* temp1 = list->createHead(2);
    IntNode* temp2 = list->insertAfter(temp1, 3);
    
    IntNode* cur = list->head;
    while(cur != nullptr) {
        cout << cur->data << endl;
        cur = cur->next;
    }
    cout << list->size << endl;

    // sample usage of stack
    IntStack* stk = new IntStack;
    stk->push(23);
    int size = stk->getSize();
    int peek = stk->getPeek();
    stk->pop();
    stk->getPeek();
    cout << size << endl;
    cout << peek << endl;

    // deallocate memory
    delete list;
    delete stk;
    list = nullptr;
    stk = nullptr;
    return 0;
}
