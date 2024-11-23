#include<iostream>
#include"queue.h"
using namespace std;
template<typename T>
void radix_sort(Queue<T>& queue, int k, int m) {
    Queue<T> temp[m];
    int exponent = 1;
    for (int i = 0; i < k; i++) {  // Ensure we only loop k times
        // Empty the main queue and distribute the elements into buckets
        while (!queue.isEmpty()) {
            T num = queue.Front();
            queue.dequeue();
            int index = (num / exponent) % m;  // Calculate bucket index
            temp[index].enqueue(num);
        }
        // Collect the numbers from the buckets and put them back into the main queue
        for (int j = 0; j < m; j++) {
            while (!temp[j].isEmpty()) {
                T num = temp[j].Front();
                temp[j].dequeue();
                queue.enqueue(num);
            }
        }
        exponent *= m;  // Move to the next digit
    }
}
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
            temp[(int)num[k]].enqueue(num);
        }
        else temp[0].enqueue(num);
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
void radixSort(Queue<string>& queue, int k,int m){
    Queue<string> temp[m]; //array of m queues
    int j = 0;
    int exponent = 1;
    k--;
    while(k>=0){   
        k--;
        Queue_fill_string(queue,exponent,temp);
        Queue_emptier_string(queue,m,temp);
        exponent*= m;
    }
}
int main(){
    Queue<int> queue(7);
    queue.enqueue(329);
    queue.enqueue(7);
    queue.enqueue(657);
    queue.enqueue(39);
    queue.enqueue(436);
    queue.enqueue(20);
    queue.enqueue(355);
    queue.print();
    int k= 3;
    int m = 10;
    radix_sort(queue,k,m);
    k = 7;
    m = 256;
    queue.print();
	// print(queue);
    // Queue<string> q(3);
    // q.enqueue("easiest");
    // q.enqueue("biggest");
    // q.enqueue("tallest");
    // radixSort(q,k,m);
    // print(q);
    return 0;
}