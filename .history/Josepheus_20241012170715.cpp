#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

// Constants for window size and text properties
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FONT_SIZE = 24;
const char* FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"; // Update this path

// Function to initialize SDL and SDL_ttf
bool initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        cerr << "SDL_Init Error: " << SDL_GetError() << endl;
        return false;
    }
    if (TTF_Init() == -1) {
        cerr << "TTF_Init Error: " << TTF_GetError() << endl;
        SDL_Quit();
        return false;
    }

    *window = SDL_CreateWindow("Josephus Problem", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!*window) {
        cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*renderer) {
        SDL_DestroyWindow(*window);
        cerr << "Renderer could not be created! SDL_Error: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

// Function to draw the Josephus circle
void drawJosephusCircle(SDL_Renderer* renderer, TTF_Font* font, const vector<int>& eliminationOrder, int currentStep) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    float radius = 200.0;
    SDL_Point center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    // Draw numbers around a circle
    for (size_t i = 0; i < eliminationOrder.size(); i++) {
        int num = eliminationOrder[i];
        double angle = 2 * M_PI * i / eliminationOrder.size();
        int x = center.x + int(radius * cos(angle)) - FONT_SIZE / 2;
        int y = center.y + int(radius * sin(angle)) - FONT_SIZE / 2;

        // Create text surface and texture
        SDL_Color color = {255, 255, 255, 255}; // White text
        if (i < currentStep) {
            color = {255, 0, 0, 255}; // Red if eliminated
        }
        string text = to_string(num);
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

        // Create text rectangle and render
        SDL_Rect textRect = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);

        // Free resources
        SDL_FreeSurface(surface);
        SDL_DestroyTexture(texture);
    }

    SDL_RenderPresent(renderer);
}

int main() {
    SDL_Window* window = nullptr;
    SDL_Renderer* renderer = nullptr;
    if (!initSDL(&window, &renderer)) {
        return 1; // SDL could not be initialized
    }

    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        cerr << "Failed to load font: " << TTF_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }

    int n = 10; // Number of people
    int k = 3;  // Every k-th person will be eliminated

    vector<int> eliminationOrder;
    for (int i = 1; i <= n; ++i) {
        eliminationOrder.push_back(i);
    }

    bool quit = false;
    SDL_Event event;
    int currentStep = 0;

    while (!quit) {
        while (SDL_PollEvent(&event) != 0) {
            if (event.type == SDL_QUIT) {
                quit = true;
            }
        }

        // Draw and update at each step
        drawJosephusCircle(renderer, font, eliminationOrder, currentStep);
        if (currentStep < eliminationOrder.size()) {
            SDL_Delay(1000); // Delay to show elimination
            currentStep++;
        }

        SDL_Delay(10); // Small delay to reduce CPU usage
    }

    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
