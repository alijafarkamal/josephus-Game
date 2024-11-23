// g++ 23L-0815_Q1.cpp $(sdl2-config --cflags --libs) -lSDL2_ttf -o JosephusProgram -lm
// ./JosephusProgram
#include <iostream>
#include <cmath>
#include <vector>
#include <SDL.h>
#include <SDL_ttf.h>
using namespace std;
template<typename T>
class Queue {
    int capacity;
    int size;
    struct Node {
    T data;
    Node* next;
    Node(T num) : data(num), next(nullptr) { }
    };
    Node* front;
    Node* rear;
public:

    Queue(int num) : size(num), capacity(0), front(nullptr), rear(nullptr) {}
    Queue() : front(nullptr), rear(nullptr), capacity(0), size(0) {}
    T dequeue() {
        if (front == nullptr) {
            return T(); // Return default if empty
        }
        Node* temp = front;
        T data = front->data;
        if (front == rear) {
            front = rear = nullptr;
        } else {
            front = front->next;
            rear->next = front;
        }
        delete temp;
        capacity--;
        return data;
    }
    bool isEmpty() {
        return capacity == 0;
    }
    void enqueue(T num) {
        Node* newNode = new Node(num);
        if (front == nullptr) {
            front = rear = newNode;
            rear->next = front; 
        } else {
            rear->next = newNode;
            rear = newNode;
            rear->next = front;
        }
        capacity++;
    }

    Node* getRear(){
        return rear;
    }
    Node* getFront() {
        return front;
    }
    T Front() {
        if(front){
            return front->data;
        }
        else return T();    
    }
    bool isFull() {
        return capacity == size;
    }
    int getSize() {
        return capacity;
    }
    void print() {
        if(front!=nullptr){
            Node* temp = front;
                do {
                    cout << temp->data << " ";
                    temp = temp->next;
                } while (temp != front && temp!=nullptr);
            cout << endl;
        }
    }
    T Rear() {
        if(rear){
            return rear->data;
        }
        else return T();  
    }
    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }
};
const int WINDOW_HEIGHT = 600;
const int FONT_SIZE = 24;
const float radius = 250.0;
const char* FONT_PATH = "/usr/share/fonts/truetype/dejavu/DejaVuSans-Bold.ttf"; // Update this path
const int WINDOW_WIDTH = 800;
void drawJosephusCircle(SDL_Renderer* renderer, TTF_Font* font, const vector<int>& order, int currentStep) {
    // SDL_SetRenderDrawColor(renderer, 10, 24, 72, 255); // Deep blue background
    // SDL_SetRenderDrawColor(renderer, 210, 210, 210, 255); // Soft gray background
    SDL_SetRenderDrawColor(renderer, 0, 120, 0, 255);
    SDL_RenderClear(renderer);
    // float radius = 250.0;
    SDL_Point center = {WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2};
    vector<bool> eliminated(order.size() + 1, false); 

    for (int step = 0; step < currentStep && step < order.size(); step++) {
        eliminated[order[step]] = true;
    }
    for (int i = 0; i <= order.size(); i++) {  
        double angle = 2 * M_PI * i / (order.size() + 1);
        int x = center.x + int(radius * cos(angle)) - FONT_SIZE / 2;
        int y = center.y + int(radius * sin(angle)) - FONT_SIZE / 2;
        SDL_Color color;
        if(eliminated[i])
        { color =SDL_Color{255, 0, 0, 255}; }
        else
        color = SDL_Color{255, 255, 255, 255};
        // SDL_Color color = eliminated[i] ? SDL_Color{255, 0, 0, 255} : SDL_Color{255, 255, 255, 255};
        string text = to_string(i);
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_Rect textRect = {x - surface->w / 2, y - surface->h / 2, surface->w, surface->h};
        SDL_RenderCopy(renderer, texture, NULL, &textRect);
        SDL_DestroyTexture(texture);
        SDL_FreeSurface(surface);
    }
    SDL_RenderPresent(renderer);
}

void fill(Queue<int>& q,int k){
    for (int i = 1; i < k; i++) {
        q.enqueue(q.Front());
        q.dequeue();
    }
}
void initiate(Queue<int>& q,int n){
    for (int i = 0; i < n; i++) {
        q.enqueue(i);
    }
}
vector<int> josephus(int& Num,int n, int k) {
    Queue<int> q;
    vector<int> eliminationOrder;
    initiate(q,n);
    while (!(q.getSize()==1)) {
        fill(q,k);
        eliminationOrder.push_back(q.Front());
        q.dequeue();
    }
    Num = q.Front();
    return eliminationOrder;
}
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
int main() {
    SDL_Renderer* renderer = nullptr;
    SDL_Window* window = nullptr;
    if (!initSDL(&window, &renderer)) {
        return 1;
    }
    TTF_Font* font = TTF_OpenFont(FONT_PATH, FONT_SIZE);
    if (!font) {
        cout << "Failed to load font: " << TTF_GetError() << endl;
        TTF_Quit();
        SDL_Quit();
        return 1;
    }
    int n = 10;  
    int k = 3;   
    int num = 0;
    vector<int> eliminationOrder = josephus(num,n, k);
    bool quit = false;
    SDL_Event e;
    int currentStep = 0;
    bool turn = true;
    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) quit = true;
        }
        if (currentStep <= eliminationOrder.size()) {  // Ensure this includes all steps
            drawJosephusCircle(renderer, font, eliminationOrder, currentStep);
            SDL_Delay(1000);  // Delay for visibility
            if (currentStep < eliminationOrder.size()) {
                currentStep++;
            } else if (currentStep == eliminationOrder.size()) {
                cout << "The winner is " << num << endl;
                currentStep++;  // Increment to end the loop correctly
            }
        }
    }
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
