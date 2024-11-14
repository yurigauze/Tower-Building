// SDLEventHandler.h
#ifndef SDLEVENTHANDLER_H
#define SDLEVENTHANDLER_H

#include "EventHandler.h"
#include <SDL2/SDL.h>

class SDLEventHandler : public EventHandler {
public:
    bool pollEvent() override {
        return SDL_PollEvent(&event);
    }
    int getEventType() override {
        return event.type;
    }
    bool isQuitEvent() override {
        return event.type == SDL_QUIT;
    }
    bool isKeyDownEvent() override {
        return event.type == SDL_KEYDOWN;
    }
    int getKeyCode() override {
        return event.key.keysym.sym;
    }

    bool isMouseButtonDownEvent() override {
        return event.type == SDL_MOUSEBUTTONDOWN; 
    }

    int getMouseX() override {
        return event.button.x; 
    }

    int getMouseY() override {
        return event.button.y; 
    }
private:
    SDL_Event event;
};

#endif // SDLEVENTHANDLER_H
