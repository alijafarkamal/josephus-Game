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
    void print() {
        if (front) {
            Node* temp = front;
            do {
                cout << temp->data << " ";
                temp = temp->next;
            } while (temp != front);
            cout << endl;
        }
    }
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
    // void fill(Queue& queue,int N){
//     for(int i = 0; i<N; i++){
//         queue.enqueue(i);
//     }
// }
// int Josephus(int N,int k){
//     if(N<1){
//         return -1;
//     }
//     if(k>=N) k = k%N;
//     int S = rand()%N;
//     Node* start = front;
//     Node* ptr = start->next;
//     int count = 0;
//     while(count<S){
//         start = ptr;
//         ptr = ptr->next;
//         count++;
//     }
//     count = 0;
//     Node* end = rear;
//     while(start!=end){
//         while(count<k){
//             start = ptr;
//             ptr = ptr->next;
//             count++;
//         }
//         start->next = ptr->next;
//         count =0;
//     }
    
//     cout<<S;
//     return 1;

// }
  
};
