#ifndef RENDERER_TEXT_H
#define RENDERER_TEXT_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>
#include <stdexcept>

class RendererText : public PortRender {
public:
    RendererText(SDL_Renderer* renderer);
    ~RendererText();

    // Corrigido para retornar bool
    bool loadFont(const std::string& id, const std::string& path, int size);

    void drawText(const std::string& fontId, const std::string& text, int x, int y, SDL_Color color);

private:
    SDL_Renderer* renderer;
    TTF_Font* font;
};

#endif // RENDERER_TEXT_H
