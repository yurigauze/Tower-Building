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
private:
    SDL_Event event;
};

#endif // SDLEVENTHANDLER_H
