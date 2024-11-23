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
    int S = rand()%N;
    while(queue.is)
    cout<<S;
    return 1;

}
int main(){
    int N = 10;
    int k = 3;
    cout<<"The survivor is "<<Josephus(N,k)<<endl;
    return 0;
}