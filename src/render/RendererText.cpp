#include "RendererText.h"

RendererText::RendererText(SDL_Renderer* renderer) : renderer(renderer), font(nullptr) {
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf");
    }
}

RendererText::~RendererText() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

bool RendererText::loadFont(const std::string& id, const std::string& path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        return false; // Retornar false se falhar
    }
    return true; // Retornar true se tiver sucesso
}

void RendererText::drawText(const std::string& fontId, const std::string& text, int x, int y, SDL_Color color) {
    if (!font) return;

    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Failed to create text surface");
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        throw std::runtime_error("Failed to create text texture");
    }

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}
