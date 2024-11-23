#include<iostream>
#include"queue.h"
using namespace std;
void fill(Queue& queue,int N){
    for(int i = 0; i<N; i++){
        queue.enqueue(i);
    }
}
void eliminator(Queue& queue,int k){
    int count = 0;
    while(count<k){
        int num = queue.dequeue();
        count++;
        if(count<k)
        queue.enqueue(num);
    }
}
int Josephus(int N,int k){
    if(N<1){
        return -1;
    }
    if(k>=N) k = k%N;
    Queue queue(N);
    fill(queue,N);
    int count = 0;
    while(!(queue.getSize()==1)){
        eliminator(queue,k);
    }
    return queue.Rear();
}
int main(){
    int N = 10;
    int k = 3;
    cout<<"The survivor is "<<Josephus(N,k)<<endl;
    return 0;
}
    // queue.print();
    // Queue result(N);
    // while(!(result.getSize()==N)){
    //  return 1;
    // }
 // queue.print();
    // cout<<S;
    // return 1;