#include<iostream>
using namespace std;
template<typename t>
struct Node {
    t data;
    Node* next;
    Node(t num) : data(num), next(nullptr) { }
};
template<typename T>
class Queue {
    int capacity;
    int size;
    Node* front;
    Node* rear;
public:
    Queue(int num) : size(num), capacity(0), front(nullptr), rear(nullptr) {}
    int dequeue() {
        T num = -1;
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
    void enqueue(T num) {
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
    Node* getRear(){
        return rear;
    }
    Node* getFront() {
        return front;
    }
    T Front() {
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
    T Rear() {
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
                temp = temp->next;
            }
        cout << endl;
    }
};
