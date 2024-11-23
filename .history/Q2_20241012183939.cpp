#include<iostream>
#include"queue.h"
using namespace std;
void Queue_fill(Queue<int>& queue,int m,Queue<int>& temp[]){
    j = 0;
    while(j<m){
        while (!(temp[j].size()==0)) {
            int num = temp[j].front();
            temp[j].pop();
            queue.enqueue(num);
        }
        j++;
    }
}
void Queue_emptier(Queue<int>& queue,int exponent,Queue<int>& temp[]){
    while (!(queue.getSize()==0)) 
    {
        int num = queue.getFront();
        queue.dequeue();
        int rem = num / exponent;
        rem %= 10;
        temp[rem].push(num);
    }
}
template<typename T>
void radix_sort(Queue<T>& queue, int k,int m){
    Queue<T> temp[m]; 
    int j = 0;
    int exponent = 1;
    while(k>=0){
        k--;
        Queue_emptier(queue,exponent,temp);
        Queue_fill(queue,m,temp)
        exponent*= m;
    }
}
template<typename t>
void print(Queue<t>& queue){
    while(!queue.empty())
    {
        cout<<queue.front()<<" ";
        queue.dequeue();
    }
    cout<<endl;
}
void radixSort(Queue<string>& queue, int k,int m){
    Queue<string> temp[m]; //array of m queues
    int j = 0;
    int exponent = 1;
    k--;
    while(k>=0){   
        k--;
        //operation for emptying original queue and putting its content in other array
        while (!(queue.size()==0)) {
            string num = queue.front();
            if(k<num.size()){
                temp[(int)num[k]].push(num);
            }
            else temp[0].push(num);
            //temp[rem].push(num);
            queue.pop();
            //cout<<"hello";
        }
        //putting back sorted content into original queue
        j = 0;
        while(j<m){
            while (!(temp[j].size()==0)) {
                string num = temp[j].front();
                queue.push(num);
                temp[j].pop();  
                //cout<<"hello";
            }
            j++;
            //cout<<endl;
        }
        exponent*= m;
    }
}
int main(){
    Queue<int> queue;
    Queue.enqueue(329);
    Queue.enqueue(7);
    Queue.enqueue(657);
    Queue.enqueue(39);
    Queue.enqueue(436);
    Queue.enqueue(20);
    Queue.enqueue(355);
    int k= 3;
    int m = 10;
    radix_sort(queue,k,m);
    k = 7;
    m = 256;
	print(queue);
    Queue<string> q;
    q.enqueue("easiest");
    q.enqueue("biggest");
    q.enqueue("tallest");
    radixSort(q,k,m);
    print(q);
    return 0;
}