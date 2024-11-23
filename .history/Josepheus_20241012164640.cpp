#include <iostream>
#include <SDL.h>
#include <vector>
#include <cmath> // Ensure you include cmath for math functions
#include "queue.h"
using namespace std;
void eliminator(Queue& queue, int k, SDL_Renderer* renderer, int screenWidth, int screenHeight) {
    int count = 0;
    while (count < k) {
        int num = queue.dequeue();
        count++;
        if (count < k)
            queue.enqueue(num);

        // Draw each step
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White background
        SDL_RenderClear(renderer);
        Node* node = queue.getFront();
        int angle = 360 / queue.getSize();
        for (int i = 0; i < queue.getSize(); i++) {
            SDL_Rect rect = {
                screenWidth / 2 + int(200 * cos(i * angle * M_PI / 180.0)) - 25,
                screenHeight / 2 + int(200 * sin(i * angle * M_PI / 180.0)) - 25,
                50, 50
            };
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue circles
            SDL_RenderFillRect(renderer, &rect);
            node = node->next;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000);  // Delay to visualize
    }
}

int Josephus(int N, int k, SDL_Renderer* renderer, int screenWidth, int screenHeight) {
    if (N < 1) {
        return -1;
    }
    if (k >= N) k = k % N;
    Queue queue(N);
    for (int i = 0; i < N; i++) {
        queue.enqueue(i);
    }
    while (!(queue.getSize() == 1)) {
        eliminator(queue, k, renderer, screenWidth, screenHeight);
    }
    return queue.Rear();
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }

    // Use -1 explicitly if SDL_WINDOWPOS_CENTERED is causing issues
    SDL_Window* window = SDL_CreateWindow("Josephus Problem", -1, -1, 800, 600, SDL_WINDOW_SHOWN);
    if (!window) {
        cout << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    // Use explicit flag value if SDL_RENDERER_PRESENTVSYNC is causing issues
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | 0x00000002);
    if (!renderer) {
        SDL_DestroyWindow(window);
        cout << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    int N = 10;  // Number of people
    int k = 5;   // Every k-th person will be eliminated
    cout << "The survivor is " << Josephus(N, k, renderer, 800, 600) << endl;

    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}