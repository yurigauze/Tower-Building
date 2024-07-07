// SDLRenderer.h
#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include "Renderer.h"
#include <SDL2/SDL.h>

class SDLRenderer : public Renderer {
public:
    SDLRenderer(SDL_Renderer* renderer) : renderer(renderer) {}
    void clear() override {
        SDL_RenderClear(renderer);
    }
    void setDrawColor(int r, int g, int b, int a) override {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    }
    void drawRect(int x, int y, int width, int height) override {
        SDL_Rect rect = {x, y, width, height};
        SDL_RenderDrawRect(renderer, &rect);
    }
    void present() override {
        SDL_RenderPresent(renderer);
    }
private:
    SDL_Renderer* renderer;
};

#endif // SDLRENDERER_H
