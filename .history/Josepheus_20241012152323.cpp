#include<iostream>
#include"queue.h"
using namespace std;
void fill(Queue& queue,int N){
    for(int i = 0; i<N; i++){
        queue.enqueue(i);
    }
}
int Josephus(int N,int k){
    if(N<1){
        return -1;
    }
    if(k>=N) k = k%N;
    Queue queue(N);

    fill(queue,N);
    // queue.print();
    int count = 0;
    while(!(queue.getSize()==1)){
        while(count<k){
            int num = queue.dequeue();
            count++;
            if(count<k)
            queue.enqueue(num);
            queue.print();
        }
        count = 0;
    }
    // queue.print();
    // return queue.Front();
    // Queue result(N);
    // while(!(result.getSize()==N)){
    // return 1;
    // }
}
    // cout<<S;
    // return 1;
int main(){
    int N = 10;
    int k = 4;
    cout<<"The survivor is "<<Josephus(N,k)<<endl;
    return 0;
}