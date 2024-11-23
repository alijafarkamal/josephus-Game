#include<iostream>
#include"queue.h"
using namespace std;
void Queue_emptier(Queue<T>& queue,int exponent,Queue<T>& temp){
    while (!(queue.size()==0)) 
    {
        int num = queue.front();
        queue.pop();
        int rem = num / exponent;
        rem %= 10;
        temp[rem].push(num);
    }
}
template<typename T>
void radix_sort(Queue<T>& queue, int k,int m){
    Queue<T> temp[m]; //array of m queues
    int j = 0;
    int exponent = 1;
    while(k>=0){
        k--;
        //operation for emptying original queue and putting its content in other array
        Queue_emptier(queue,exponent,temp);
        //putting back sorted content into original queue
        j = 0;
        while(j<m){
            while (!(temp[j].size()==0)) {
                T num = temp[j].front();
                temp[j].pop();
                Queue.push(num);
                //cout<<"hello";
            }
            j++;
            //cout<<endl;
        }
        exponent*= m;
    }
}
template<typename t>
void print(queue<t>& Queue){

    while(!Queue.empty())
    {
        cout<<Queue.front()<<" ";
        Queue.pop();
    }
    cout<<endl;
}
void radixSort(queue<string>& Queue, int k,int m){
    queue<string> temp[m]; //array of m queues
    int j = 0;
    int exponent = 1;
    k--;
    while(k>=0){   
        k--;
        //operation for emptying original queue and putting its content in other array
        while (!(Queue.size()==0)) {
            string num = Queue.front();
            if(k<num.size()){
                temp[(int)num[k]].push(num);
            }
            else temp[0].push(num);
            //temp[rem].push(num);
            Queue.pop();
            //cout<<"hello";
        }
        //putting back sorted content into original queue
        j = 0;
        while(j<m){
            while (!(temp[j].size()==0)) {
                string num = temp[j].front();
                Queue.push(num);
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
    queue<int> Queue;
    Queue.push(329);
    Queue.push(7);
    Queue.push(657);
    Queue.push(39);
    Queue.push(436);
    Queue.push(20);
    Queue.push(355);
    int k= 3;
    int m = 10;
    radix_sort(Queue,k,m);
    k = 7;
    m = 256;
	print(Queue);
    queue<string> q;
    q.push("easiest");
    q.push("biggest");
    q.push("tallest");
    radixSort(q,k,m);
    print(q);
    return 0;
}