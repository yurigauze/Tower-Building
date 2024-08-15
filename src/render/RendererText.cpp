#include "RendererText.h"
#include <stdexcept>

RendererText::RendererText(SDL_Renderer* renderer)
    : renderer(renderer), font(nullptr) {
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }
}

RendererText::~RendererText() {
    if (font) {
        TTF_CloseFont(font);
    }
    TTF_Quit();
}

bool RendererText::initializeFont(const std::string& path, int size) {
    if (font) {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        return false; // Font loading failed
    }
    return true; // Font loaded successfully
}

void RendererText::drawText(const std::string& text, int x, int y, SDL_Color color) {
    if (!font) {
        throw std::runtime_error("Font is not loaded");
    }
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Failed to create text surface: " + std::string(TTF_GetError()));
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        throw std::runtime_error("Failed to create text texture: " + std::string(SDL_GetError()));
    }
    SDL_Rect dstRect = { x, y, surface->w, surface->h };
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}
