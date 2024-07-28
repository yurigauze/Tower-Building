// SDLRenderer.h
#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include "PortRender.h"
#include <SDL2/SDL.h>

class SDLRenderer : public PortRender {
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

    void drawLine(int x1, int y1, int x2, int y2) override {
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }

    void drawCircle(int x, int y, int radius) override {
        // Implementação básica de círculo usando o algoritmo de B  resenham
        int offsetX = 0;
        int offsetY = radius;
        int d = radius - 1;
        while (offsetX <= offsetY) {
            SDL_RenderDrawPoint(renderer, x + offsetX, y + offsetY);
            SDL_RenderDrawPoint(renderer, x + offsetY, y + offsetX);
            SDL_RenderDrawPoint(renderer, x - offsetX, y + offsetY);
            SDL_RenderDrawPoint(renderer, x - offsetY, y + offsetX);
            SDL_RenderDrawPoint(renderer, x + offsetX, y - offsetY);
            SDL_RenderDrawPoint(renderer, x + offsetY, y - offsetX);
            SDL_RenderDrawPoint(renderer, x - offsetX, y - offsetY);
            SDL_RenderDrawPoint(renderer, x - offsetY, y - offsetX);
            if (d >= 2 * offsetX) {
                d -= 2 * offsetX + 1;
                offsetX++;
            } else if (d < 2 * (radius - offsetY)) {
                d += 2 * offsetY - 1;
                offsetY--;
            } else {
                d += 2 * (offsetY - offsetX - 1);
                offsetY--;
                offsetX++;
            }
        }
    }

    void drawPoint(int x, int y) override {
        SDL_RenderDrawPoint(renderer, x, y);
    }

    void present() override {
        SDL_RenderPresent(renderer);
    }
private:
    SDL_Renderer* renderer;
};

#endif // SDLRENDERER_H
