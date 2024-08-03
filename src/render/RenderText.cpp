#include "RenderText.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <stdexcept>

TextRenderer::TextRenderer(SDL_Renderer* renderer, const std::string& fontPath, int fontSize)
    : renderer_(renderer) {
    font_ = TTF_OpenFont(fontPath.c_str(), fontSize);
    if (!font_) {
        throw std::runtime_error("Failed to load font");
    }
}

TextRenderer::~TextRenderer() {
    TTF_CloseFont(font_);
}

void TextRenderer::renderText(const std::string& text, int x, int y, const SDL_Color& color) {
    SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
    if (!surface) {
        throw std::runtime_error("Failed to create text surface");
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        throw std::runtime_error("Failed to create text texture");
    }
    SDL_Rect destRect = {x, y, 0, 0};
    SDL_QueryTexture(texture, nullptr, nullptr, &destRect.w, &destRect.h);
    SDL_RenderCopy(renderer_, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}
