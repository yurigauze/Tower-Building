// SDLRenderer.cpp
#include "SDLRenderer.h"
#include <iostream>
#include <ostream>
#include <stdexcept>

SDLRenderer::SDLRenderer(SDL_Renderer *renderer)
    : renderer(renderer), font(nullptr) {
}

SDLRenderer::~SDLRenderer() {
    for (auto& pair : textures) {
        SDL_DestroyTexture(pair.second);
    }
    textures.clear();
    if (font) {
        TTF_CloseFont(font);
    }
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

void SDLRenderer::drawPoint(int x, int y) {
    SDL_RenderDrawPoint(renderer, x, y);
}

void SDLRenderer::present() {
    SDL_RenderPresent(renderer);
}

bool SDLRenderer::loadFont(const std::string &path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void SDLRenderer::drawText(const std::string &text, int x, int y, int r, int g, int b, int a) {
    if (!font) {
        std::cerr << "Fonte não carregada!" << std::endl;
        return;
    }
    SDL_Color sdlColor = {static_cast<Uint8>(r), static_cast<Uint8>(g),
                          static_cast<Uint8>(b), static_cast<Uint8>(a)};
    SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), sdlColor);
    if (!surface) {
        std::cerr << "Erro ao criar superfície de texto: " << TTF_GetError() << std::endl;
        return;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (!texture) {
        std::cerr << "Erro ao criar textura a partir da superfície: " << SDL_GetError() << std::endl;
        return;
    }
    SDL_Rect dstRect = {x, y, surface->w, surface->h};
    SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
    SDL_DestroyTexture(texture);
}


bool SDLRenderer::loadTexture(const std::string &id, const std::string &filePath) {
    SDL_Surface *tempSurface = IMG_Load(filePath.c_str());
    if (!tempSurface) {
        std::cerr << "Erro ao carregar a superfície da imagem: " << IMG_GetError() << std::endl;
        return false;
    }
    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, tempSurface);
    SDL_FreeSurface(tempSurface);
    if (!texture) {
        std::cerr << "Erro ao criar textura: " << SDL_GetError() << std::endl;
        return false;
    }
    textures[id] = texture;
    return true;
}


SDL_Texture* SDLRenderer::getTexture(const std::string& id) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        return it->second;
    }
    return nullptr;
}

void SDLRenderer::drawTexture(const std::string &id, int x, int y, SDL_Rect *srcRect) {
    auto it = textures.find(id);
    if (it != textures.end()) {
        SDL_Rect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = srcRect->w;
        destRect.h = srcRect->h;
        SDL_RenderCopy(renderer, it->second, srcRect, &destRect);
    } else {
        std::cerr << "Texture with id " << id << " not found." << std::endl;
    }
}

void SDLRenderer::destroyTexture(SDL_Texture* texture) {
    SDL_DestroyTexture(texture);
}


SDL_Renderer *SDLRenderer::getRenderer() const {
    return renderer;
}