#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include "queue.h"

using namespace std;

void eliminator(Queue& queue, int k, SDL_Renderer* renderer, TTF_Font* font, int screenWidth, int screenHeight) {
    int count = 0;
    SDL_Color textColor = {255, 255, 255, 255}; // White text
    while (count < k) {
        int num = queue.dequeue();
        count++;
        if (count < k)
            queue.enqueue(num);

        // Draw each step
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
        SDL_RenderClear(renderer);
        Node* node = queue.getFront();
        int angle = 360 / queue.getSize();
        for (int i = 0; i < queue.getSize(); i++) {
            int x = screenWidth / 2 + int(200 * cos(i * angle * M_PI / 180.0)) - 25;
            int y = screenHeight / 2 + int(200 * sin(i * angle * M_PI / 180.0)) - 25;
            SDL_Rect rect = {x, y, 50, 50};
            SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue boxes
            SDL_RenderFillRect(renderer, &rect);

            // Render text
            char text[10];
            sprintf(text, "%d", node->data);
            SDL_Surface* surface = TTF_RenderText_Solid(font, text, textColor);
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_Rect textRect = {x, y, surface->w, surface->h};
            SDL_RenderCopy(renderer, texture, NULL, &textRect);
            SDL_FreeSurface(surface);
            SDL_DestroyTexture(texture);

            node = node->next;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000); // Delay to visualize
    }
}

int Josephus(int N, int k, SDL_Renderer* renderer, TTF_Font* font, int screenWidth, int screenHeight) {
    if (N < 1) return -1;
    if (k >= N) k = k % N;
    Queue queue(N);
    for (int i = 0; i < N; i++) {
        queue.enqueue(i);
    }
    while (queue.getSize() > 1) {
        eliminator(queue, k, renderer, font, screenWidth, screenHeight);
    }
    return queue.Rear();
}

int main(int argc, char* argv[]) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return 1;
    }
    if (TTF_Init() == -1) {
        cerr << "TTF_Init Error: " << TTF_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow("Josephus Problem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    TTF_Font* font = TTF_OpenFont("/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf", 24);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() <<endl;
    }
    int N = 10;
    int k = 5;
    cout << "The survivor is " << Josephus(N, k, renderer, font, 800, 600) << endl;
    bool quit = false;
    SDL_Event e;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        SDL_Delay(100); // Reduce CPU usage
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
