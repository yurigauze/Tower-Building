// SDLImplements.cpp
#include "SDLImplements.h"
#include <stdexcept> 

SDLImplements::SDLImplements(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = fullscreen ? SDL_WINDOW_FULLSCREEN : 0;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }

    window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
    if (!window) {
        SDL_Quit();
        throw std::runtime_error("Failed to create window");
    }

    sdlRenderer = SDL_CreateRenderer(window, -1, 0);
    if (!sdlRenderer) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        throw std::runtime_error("Failed to create renderer");
    }

    renderer = new SDLRenderer(sdlRenderer);
    eventHandler = new SDLEventHandler();
}

SDLImplements::~SDLImplements() {
    delete renderer;
    delete eventHandler;
    SDL_DestroyRenderer(sdlRenderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
