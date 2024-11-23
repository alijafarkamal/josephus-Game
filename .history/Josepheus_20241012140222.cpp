#include<iostream>
#include"queue.h"
using namespace std;
int Josephus(int N,int k){
    Queue queue(10);

    if(N<1){
        return 1;
    }

}
int main(){
    int N = 10;
    int k = 3;
    cout<<Josepheus(N,k);
    return 0;
}