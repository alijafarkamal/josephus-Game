// #include<iostream>
// #include"queue.h"
// using namespace std;
// void eliminator(Queue& queue,int k){
//     int count = 0;
//     while(count<k){
//         int num = queue.dequeue();
//         count++;
//         if(count<k)
//         queue.enqueue(num);
//     }
// }
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
//     int count = 0;
//     while(!(queue.getSize()==1)){
//         eliminator(queue,k);
//     }
//     return queue.Rear();
// }
// int main(){
//     int N = 10;
//     int k = 5;
//     cout<<"The survivor is "<<Josephus(N,k)<<endl;
//     return 0;
// }
//     // queue.print();
//     // Queue result(N);
//     // while(!(result.getSize()==N)){
//     //  return 1;
//     // }
//  // queue.print();
//     // cout<<S;
//     // return 1;
// test_sdl.cpp
#include <SDL.h>
#include <iostream>

int main() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cerr << "SDL_Init Error: " << SDL_GetError() << std::endl;
        return 1;
    }
    std::cout << "SDL initialized successfully" << std::endl;
    SDL_Quit();
    return 0;
}
