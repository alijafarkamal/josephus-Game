#include<iostream>
#include"queue.h"
using namespace std;
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
//     Queue queue(N);
//     fill(queue,N);
//     Queue result(N);
//     int S = rand()%N;
//     while(!(result.getSize()==N)){
        
//     }
    
//     cout<<S;
//     return 1;

// }
int main(){
    int N = 10;
    int k = 3;
    Queue queue(10);
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    queue.enqueue(4);
    queue.enqueue(5);
    queue.enqueue(6);
    queue.enqueue(7);
    queue.enqueue(8);
    queue.enqueue(9);
    queue.enqueue(10);
    cout<<"The survivor is "<<queue.Josephus(N,k)<<endl;
    queue.print();
    return 0;
}