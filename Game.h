#define Game_h
#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include "box2d/box2d.h"

class Game{
    public:
        b2World* world_;
        bool isRunning;
        SDL_Window* window;
        SDL_Renderer* renderer;
        SDL_Surface* surface;

        Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
        bool running() {return isRunning;};
        void handleEvents();
        void update();
        void render();
        void clean();

};