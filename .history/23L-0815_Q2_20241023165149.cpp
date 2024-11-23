#include<iostream>
using namespace std;
template<typename T>
class Queue {
    int capacity;
    int size;
    struct Node {
    T data;
    Node* next;
    Node(T num) : data(num), next(nullptr) { }
    };
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
};
template<typename t>
void print(Queue<t>& queue){
    while(!queue.isEmpty())
    {
        cout<<queue.Front()<<" ";
        queue.dequeue();
    }
    cout<<endl;
}
void Queue_fill_string(Queue<string>& queue,int k,Queue<string>* temp){
    while (!(queue.getSize()==0)) {
        string num = queue.Front();
        if(k<num.size()){
            temp[(toascii(num[k]))].enqueue(num);
        }
        else {
        temp[0].enqueue(num);
        }
        queue.dequeue();
    }
}
void Queue_emptier_string(Queue<string>& queue,int m,Queue<string>* temp){
    int j = 0;
        while(j<m){
            while (!(temp[j].getSize()==0)) {
                string num = temp[j].Front();
                queue.enqueue(num);
                temp[j].dequeue();  
            }
            j++;
        }
}
void Queue_fill_int(Queue<int>& queue,int m,Queue<int>* temp){
    int j = 0;
    while(j<m){
        while (!(temp[j].getSize()==0)) {
            int num = temp[j].Front();
            temp[j].dequeue();
            queue.enqueue(num);
        }
        j++;
    }
}
void Queue_emptier_int(Queue<int>& queue,int k,Queue<int>* temp){
    while (!(queue.getSize()==0)) 
        {
            int num = queue.Front();
            queue.dequeue();
            int rem = num / k;
            rem %= 10;
            temp[rem].enqueue(num);
        } 
}
void radixSort(Queue<string>& queue, int k,int m){ 
    int exponent = 1;
    Queue<string> temp[m]; //array of m queues
    while(k>0){   
        Queue_fill_string(queue,exponent,temp);
        Queue_emptier_string(queue,m,temp);
        // queue.print();
        exponent++;
        k--;
    }
}
template<typename T>
void radix_sort(Queue<T>& queue, int k,int m){
    Queue<T> temp[m]; 
    int j = 0;
    int exponent = 1;
    while(k>0){
        Queue_emptier_int(queue,exponent,temp);
        Queue_fill_int(queue,m,temp);
        exponent*= m;
        k--;
    }
}
int main(){
    Queue<int> queue(7);
    queue.enqueue(329);
    queue.enqueue(-7);
    queue.enqueue(657);
    queue.enqueue(39);
    queue.enqueue(436);
    queue.enqueue(20);
    queue.enqueue(355);
    int k= 3;
    int m = 10;  
    radix_sort(queue,k,m);
    print(queue);
    k = 7;    
    m = 256;
    Queue<string> q(3);
    q.enqueue("easiest");
    q.enqueue("biggest");
    q.enqueue("tallest");
    radixSort(q,k,m);
    print(q);
    return 0;
}