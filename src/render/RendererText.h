#ifndef RENDERER_TEXT_H
#define RENDERER_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>
#include "PortRender.h"  // Inclua o cabeçalho correto

class RendererText : public PortRender {
public:
    RendererText(SDL_Renderer* renderer);
    ~RendererText();

    // Método para configurar a fonte
    bool initializeFont(const std::string& path, int size);
    void drawText(const std::string& text, int x, int y, SDL_Color color);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
};

#endif // RENDERER_TEXT_H
