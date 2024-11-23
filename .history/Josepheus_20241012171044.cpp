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
const char* FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"; // Update this path
// const char* FONT_PATH = "path/to/your/font.ttf"; // Ensure you provide a valid path to the TTF font file

// Function to solve the Josephus problem and return the elimination order
vector<int> josephus(int n, int k) {
    queue<int> q;
    vector<int> eliminationOrder;

    // Fill the queue with people numbered 1 to n
    for (int i = 1; i <= n; i++) {
        q.push(i);
    }

    // Perform the elimination process
    while (!q.empty()) {
        for (int i = 1; i < k; i++) {
            q.push(q.front());
            q.pop();
        }
        eliminationOrder.push_back(q.front());
        q.pop();
    }

    return eliminationOrder;
}

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
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!*window || !*renderer) {
        cerr << "SDL Error: " << SDL_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

// Function to draw the Josephus circle with current eliminations highlighted
void drawJosephusCircle(SDL_Renderer* renderer, TTF_Font* font, const vector<int>& order, int currentStep) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);  // Black background
    SDL_RenderClear(renderer);

    float radius = 250.0;
    SDL_Point center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};

    for (size_t i = 0; i < order.size(); i++) {
        double angle = 2 * M_PI * i / order.size();
        int x = center.x + int(radius * cos(angle)) - FONT_SIZE / 2;
        int y = center.y + int(radius * sin(angle)) - FONT_SIZE / 2;

        SDL_Color color = (i < currentStep) ? SDL_Color{255, 0, 0, 255} : SDL_Color{255, 255, 255, 255};
        string text = to_string(order[i]);
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

    int n = 10;  // Number of people
    int k = 3;   // Every k-th person will be eliminated
    vector<int> eliminationOrder = josephus(n, k);

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
