#include <iostream>
using namespace std;

struct IntNode {
    int data;
    IntNode *next;
};

struct IntList {
    IntNode* head = nullptr;
    int size = 0;
    IntNode* createHead(int _data) {
        if(head == nullptr) {
            size++;
            head = new IntNode;
            head->next = nullptr;
            head->data = _data;
            return head;
        } else {
            cout << "ERROR: Existing head, already exists" << endl;
            return nullptr;
        }
    }
    IntNode* insertAfter(IntNode*& prevNode, int _data) {
        if(prevNode == nullptr) {
            cout << "ERROR: This node does not exist" << endl;
            return nullptr;
        }
        size++;
        IntNode* newNode = new IntNode;
        newNode->data = _data;
        newNode->next = prevNode->next;
        prevNode->next = newNode;

        return newNode;
    }
    IntNode* getHead() {
        if(head == nullptr) {
            cout << "ERROR: Head does not exist" << endl;
            return nullptr;
        }
        return head;
    }
    IntNode* getAfter(IntNode* prevNode) {
        if(prevNode == nullptr) {
            cout << "ERROR: This node does not exist" << endl;
            return nullptr;
        }
        IntNode* newNode = prevNode->next;
        return newNode;
    }
    void deleteNode(IntNode*& node) {
        if(node == nullptr || size < 1) {
            cout << "ERROR: This node does not exist" << endl;
            return;
        } else if(node == head) {
            size--;
            head = head->next;
            delete node;
            node = nullptr;
            return;
        }
        IntNode* temp = head;
        for(int i = 0; i < size; i++) {
            if(temp->next != nullptr && temp->next == node) {
                temp->next = node->next;
                delete node;
                node = nullptr;
                size--;
                return;
            }
            temp = temp->next;
        }
        cout << "ERROR: Node does not exist" << endl;
        return;
    }
    ~IntList() {
        while (head != nullptr) {
            IntNode* temp = head;
            head = head->next;
            delete temp;
            temp = nullptr;
        }
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
        temp = nullptr;
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
            temp = nullptr;
        }
    }
};

int main(){
    // insert code below
    IntList* list = new IntList;
    IntNode* temp1 = list->createHead(2);
    IntNode* temp2 = list->insertAfter(temp1, 3);
    
    IntNode* cur = list->head;
    while(cur != nullptr) {
        cout << cur->data << endl;
        cur = cur->next;
    }
    cout << list->size << endl;

    Stack* stk = new Stack;
    stk->push(23);
    int size = stk->getSize();
    int peek = stk->getPeek();
    stk->pop();
    stk->getPeek();
    cout << size << endl;
    cout << peek << endl;

    delete list;
    delete stk;
    list = nullptr;
    stk = nullptr;
    return 0;
}
