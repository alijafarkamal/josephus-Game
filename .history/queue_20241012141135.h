#include <iostream>
using namespace std;
struct Node {
    Node* next;
    int data;
    Node(int num) : data(num), next(nullptr) { }
};
class Queue {
    int capacity;
    int size;
    Node* front;
    Node* rear;
public:
    Queue(int num) : size(num), capacity(0), front(nullptr), rear(nullptr) {}
    void enqueue(int num) {
        if (capacity < size) {
            Node* newNode = new Node(num);
            if (front == nullptr) {
                front = rear = newNode;
            } else {
                rear->next = newNode;
                rear = newNode;
            }
            capacity++;
        }
    }
    void dequeue() {
        if (front != nullptr) {
            Node* temp = front;
            front = front->next;
            delete temp;
            if (front == nullptr) {
                rear = nullptr;
            }
            capacity--;
        }
    }

    bool isFull() {
        return capacity == size;
    }

    int getSize() {
        return capacity;
    }

    bool isEmpty() {
        return capacity == 1;
    }

    int Front() {
        return front ? front->data : -1; 
    }

    int Rear() {
        return rear ? rear->data : -1; 
    }

    void print() {
        Node* temp = front;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    ~Queue() {
        Node* temp = front;
        while (temp != nullptr) {
            Node* next = temp->next;
            delete temp;
            temp = next;
        }
    }
};
