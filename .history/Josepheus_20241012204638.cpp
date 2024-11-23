#include <iostream>
#include <cmath>
#include <SDL.h>
#include <SDL_ttf.h>
#include "queue.h"

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FONT_SIZE = 24;
const char* FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";  // Ensure this path is correct

bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cout << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }
    if (TTF_Init() == -1) {
        cout << "TTF_Init Error: " << TTF_GetError() << endl;
        SDL_Quit();
        return false;
    }
    *window = SDL_CreateWindow("Josephus Problem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*window || !*renderer) {
        cout << "SDL Error: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    return true;
}

void drawJosephusCircle(SDL_Renderer* renderer, TTF_Font* font, Queue<int>& queue, int k) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);
    float radius = 250.0;
    SDL_Point center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    int n = queue.getSize();
    int count = 0;
    int angleIncrement = 360 / n;

    for (int i = 0; i < n; i++) {
        int angle = angleIncrement * i;
        int x = center.x + int(radius * cos(angle * M_PI / 180.0)) - FONT_SIZE / 2;
        int y = center.y + int(radius * sin(angle * M_PI / 180.0)) - FONT_SIZE / 2;

        SDL_Color color = (i < count) ? SDL_Color{255, 0, 0, 255} : SDL_Color{255, 255, 255, 255}; // Assume you have a way to mark eliminated participants
        string text = to_string(queue.Front());
        queue.dequeue();  // For visualizing the process
        queue.enqueue(text);  // Rotate the queue

        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {x, y, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!initSDL(&window, &renderer)) {
        return 1;
    }

    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int n = 10;  // Number of people
    int k = 3;   // Every k-th person will be eliminated
    Queue<int> queue;
    for (int i = 0; i < n; i++) {
        queue.enqueue(i);
    }

    bool quit = false;
    SDL_Event e;
    while (!quit && queue.getSize() > 1) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        drawJosephusCircle(renderer, font, queue, k);
        SDL_Delay(1000);  // Delay for visualization
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
