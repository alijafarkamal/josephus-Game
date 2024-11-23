#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <SDL.h>
#include <SDL_ttf.h>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int FONT_SIZE = 24;
const char* FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf";  // Ensure you provide a valid path

vector<int> josephus(int n, int k) {
    queue<int> q;
    vector<int> eliminationOrder;

    // Fill the queue with people numbered 0 to n-1
    for (int i = 0; i < n; i++) {
        q.push(i);
    }

    while (!q.empty()) {
        // Skip k-1 persons
        for (int i = 1; i < k; i++) {
            q.push(q.front());
            q.pop();
        }
        // The k-th person is eliminated
        eliminationOrder.push_back(q.front());
        q.pop();
    }

    return eliminationOrder;
}


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
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*window || !*renderer) {
        cerr << "SDL Error: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }
    return true;
}

void drawJosephusCircle(SDL_Renderer* renderer, TTF_Font* font, const vector<int>& eliminationOrder, int currentStep) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);

    int n = 10; // Total number of people
    float radius = 250.0;
    SDL_Point center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    static vector<bool> eliminated(n, false); // Track eliminated positions, static to persist state

    // Update the eliminated array based on current step
    if (currentStep < eliminationOrder.size()) {
        eliminated[eliminationOrder[currentStep]] = true; // Mark current step as eliminated
    }

    // Draw all positions with eliminated ones in red
    for (int i = 0; i < n; i++) {
        double angle = 2 * M_PI * i / n;
        int x = center.x + int(radius * cos(angle)) - FONT_SIZE;
        int y = center.y + int(radius * sin(angle)) - FONT_SIZE;

        string text = to_string(i);
        SDL_Color color = eliminated[i] ? SDL_Color{255, 0, 0, 255} : SDL_Color{255, 255, 255, 255}; // Red if eliminated
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
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

    vector<int> eliminationOrder = josephus(10, 3);
    bool quit = false;
    SDL_Event e;
  int currentStep = 0;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }

        drawJosephusCircle(renderer, font, eliminationOrder, currentStep);

        if (currentStep < eliminationOrder.size()) {
            SDL_Delay(1000);  // Delay for 1 second to show each elimination
            currentStep++;
        } else {
            // Optionally keep the window open or restart the process
            // SDL_Delay(1000); // Keep showing the final state or handle as needed
        }

        SDL_Delay(100);  // Reduce CPU usage
    }


    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
