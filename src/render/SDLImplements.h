// SDLManager.h
#ifndef SDLIMPLEMENTS_H
#define SDLIMPLEMENTS_H

#include "PortRender.h"
#include "EventHandler.h"
#include <SDL2/SDL.h>
#include "SDLRenderer.h"
#include "SDLEventHandler.h"
#include "../utils/Constants.h"

class SDLImplements {
public:
    // Construtor e destrutor
    SDLImplements(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    ~SDLImplements();

    // Métodos de acesso
    PortRender* getRenderer() const { return renderer; }
    EventHandler* getEventHandler() const { return eventHandler; }

private:
    SDL_Window* window;
    SDL_Renderer* sdlRenderer;
    SDLRenderer* renderer;
    SDLEventHandler* eventHandler;
};

#endif // SDLImplements_H
