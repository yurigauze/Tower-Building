#ifndef IRENDERER_H
#define IRENDERER_H

#include <SDL2/SDL.h>

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void render(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest) = 0;
    virtual void renderWithRotation(SDL_Texture* texture, SDL_Rect* src, SDL_Rect* dest, double angle) = 0;
};

#endif // IRENDERER_H
