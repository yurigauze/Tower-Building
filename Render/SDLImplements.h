// SDLManager.h
#ifndef SDLIMPLEMENTS_H
#define SDLIMPLEMENTS_H

#include "Renderer.h"
#include "EventHandler.h"
#include <SDL2/SDL.h>
#include "SDLRenderer.h"
#include "SDLEventHandler.h"
#include "../Constants.h"

class SDLImplements {
public:
    SDLImplements(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    ~SDLImplements();

    Renderer* getRenderer() const { return renderer; }
    EventHandler* getEventHandler() const { return eventHandler; }

private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    Renderer* renderer;
    EventHandler* eventHandler;
};

#endif // SDLImplements_H
