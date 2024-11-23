#include<iostream>
using namespace std;
struct Node {
    int data;
    Node* next;
    Node(int num) : data(num), next(nullptr) { }
};
class Queue {
    int capacity;
    int size;
    Node* front;
    Node* rear;
public:
    Queue(int num) : size(num), capacity(0), front(nullptr), rear(nullptr) {}
        int dequeue() {
        int num = -1;
        if (front != nullptr) {
            if (front == rear) { 
                num = front->data;
                delete front;
                front = rear = nullptr;
            } else {
                Node* temp = front;
                num = temp->data;
                front = front->next;
                rear->next = front; 
                delete temp;
            }
            capacity--; 
        }
        return num;
    }
    bool isEmpty() {
        return capacity == 0;
    }
    void enqueue(int num) {
        if (capacity < size) {
            Node* newNode = new Node(num);
            if (front == nullptr) {
                front = rear = newNode;
                rear->next = front; 
            } else {
                rear->next = newNode;
                rear = newNode;
                rear->next = front;
            }
            capacity++;
        }
    }

    Node* getFront() const {
        return front;
    }
    int Front() {
        if(front){
            return front->data;
        }    
        else return -1;
    }
    bool isFull() {
        return capacity == size;
    }
    int getSize() {
        return capacity;
    }
    int Rear() {
        if(rear){
            return rear->data;
        }
        else return -1;
    }
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    void print() {
            Node* temp = front;
            while(temp != front){
                cout<<temp->data<<" ";
                temp = temp->data;
            }
            cout << endl;
    }

};
