#include<iostream>
using namespace std;
template<typename T>
class Queue {
    struct Node {
    T data;
    Node* next;
    Node(T num) : data(num), next(nullptr) { }
    };
    int capacity;
    int size;
    Node* front;
    Node* rear;
public:

    Queue(int num) : size(num), capacity(0), front(nullptr), rear(nullptr) {}
    Queue() : front(nullptr), rear(nullptr), capacity(0), size(0) {}
T dequeue() {
    if (front == nullptr) {
        return T(); // Return default if empty
    }

    Node* temp = front;
    T data = front->data;
    if (front == rear) {
        front = rear = nullptr;
    } else {
        front = front->next;
        rear->next = front;
    }
    delete temp;
    capacity--;
    return data;
}
    bool isEmpty() {
        return capacity == 0;
    }
void enqueue(T num) {
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
        else return T();    
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
        else return T();  
    }
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    void print() {
        if(front!=nullptr){
            Node* temp = front;
                do {
                    cout << temp->data << " ";
                    temp = temp->next;
                } while (temp != front && temp!=nullptr);
            cout << endl;
        }
 
    }
};
