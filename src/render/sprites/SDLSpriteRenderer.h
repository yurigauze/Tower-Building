#ifndef SDLSPRITERENDERER_H
#define SDLSPRITERENDERER_H

#include "IRenderer.h"
#include <SDL2/SDL.h>

class SDLSpriteRenderer : public IRenderer {
private:
    SDL_Renderer* sdlRenderer;

public:
    SDLSpriteRenderer(SDL_Renderer* renderer) : sdlRenderer(renderer) {}

    void render(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest) override {
        SDL_RenderCopy(sdlRenderer, texture, src, dest);
    }

    void renderWithRotation(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest, double angle) override {
        SDL_RenderCopyEx(sdlRenderer, texture, src, dest, angle, nullptr, SDL_FLIP_NONE);
    }
};

#endif // SDLSPRITERENDERER_H
