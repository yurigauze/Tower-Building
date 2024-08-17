#include "SDLRenderer.h"
#include <stdexcept>

SDLRenderer::SDLRenderer(SDL_Renderer *renderer) : renderer(renderer), font(nullptr) {
    if (TTF_Init() == -1) {
        throw std::runtime_error("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
    }
}

SDLRenderer::~SDLRenderer() {
    if (font) {
        TTF_CloseFont(font);
    }
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    TTF_Quit();
}

void SDLRenderer::clear() {
    SDL_RenderClear(renderer);
}

void SDLRenderer::setDrawColor(int r, int g, int b, int a) {
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

void SDLRenderer::drawRect(int x, int y, int width, int height) {
    SDL_Rect rect = {x, y, width, height};
    SDL_RenderDrawRect(renderer, &rect);
}

void SDLRenderer::drawLine(int x1, int y1, int x2, int y2) {
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}

void SDLRenderer::drawCircle(int x, int y, int radius) {
    // Implement drawCircle using SDL functions
}

void SDLRenderer::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}

bool SDLRenderer::loadFont(const std::string& path, int size) {
    if (font) {
        TTF_CloseFont(font);
    }
    font = TTF_OpenFont(path.c_str(), size);
    return font != nullptr;
}

void SDLRenderer::drawText(const std::string& text, int x, int y, int r, int g, int b, int a) {
    if (!font) {
        throw std::runtime_error("Font is not loaded");
    }
    SDL_Color color = {static_cast<Uint8>(r), static_cast<Uint8>(g), static_cast<Uint8>(b), static_cast<Uint8>(a)};
    SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect destRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &destRect);
    SDL_DestroyTexture(texture);
}

bool SDLRenderer::loadTexture(const std::string& id, const std::string& filename) {
    SDL_Surface* surface = IMG_Load(filename.c_str());
    if (!surface) {
        return false;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        return false;
    }
    textures[id] = texture;
    return true;
}

void SDLRenderer::drawTexture(const std::string& id, int x, int y, SDL_Rect* srcRect) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        SDL_Rect destRect = {x, y, srcRect ? srcRect->w : 0, srcRect ? srcRect->h : 0};
        SDL_RenderCopy(renderer, it->second, srcRect, &destRect);
    }
}

SDL_Renderer* SDLRenderer::getRenderer() const {
    return renderer; 
}
