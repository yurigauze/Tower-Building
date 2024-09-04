#include "Sprites.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Sprites::Sprites(const std::string &id, const std::string &filePath,
                 PortRender* renderer, int frameWidth, int frameHeight,
                 int totalFrames, float frameTime)
    : id(id), frameWidth(frameWidth), frameHeight(frameHeight),
      currentFrame(0), totalFrames(totalFrames),
      frameTime(frameTime), currentFrameTime(0.0f), renderer(renderer) {
    // Carregar textura
    bool loadSuccess = renderer->loadTexture(id, filePath);
    if (loadSuccess) {
        texture = renderer->getTexture(id); 

        if (frameWidth <= 0 || frameHeight <= 0) {
            // Use a imagem inteira se frameWidth ou frameHeight não estiverem definidos
            SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
            frameWidth = srcRect.w;
            frameHeight = srcRect.h;
        } else {
            srcRect = {0, 0, frameWidth, frameHeight};
        }
        destRect = {0, 0, frameWidth, frameHeight};
    } else {
        texture = nullptr;
        std::cerr << "Erro ao carregar textura: " << filePath << std::endl;
    }
}

Sprites::~Sprites() {
    if (texture) {
         std::cerr << "Destruiu?" << std::endl;
        renderer->destroyTexture(texture);
    }
}

void Sprites::update(float deltaTime) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= frameTime) {
        currentFrame = (currentFrame + 1) % totalFrames;
        srcRect.x = currentFrame * frameWidth;
        currentFrameTime = 0.0f;
    }
}

void Sprites::render(SDL_Renderer *renderer, int x, int y, int width, int height) {
    if (texture) {
        destRect.x = x;
        destRect.y = y;
        destRect.w = width;
        destRect.h = height;
        
        SDL_RenderCopy(renderer, texture, &srcRect, &destRect);
    } else {
        std::cerr << "Texto não carregado" << std::endl;
    }
}

void Sprites::renderFullImage(SDL_Renderer *renderer, int x, int y, int width, int height) {
    if (texture) {
        SDL_Rect fullRect = {0, 0, srcRect.w, srcRect.h}; // SrcRect deve cobrir a textura inteira
        destRect.x = x;
        destRect.y = y;
        destRect.w = width;
        destRect.h = height;
        SDL_RenderCopy(renderer, texture, &fullRect, &destRect);
    } else {
        std::cerr << "Texto não carregado" << std::endl;
    }
}

void Sprites::renderWithRotation(SDL_Renderer* renderer, int x, int y, int width, int height, double angle) {
    SDL_Rect destRect = { x, y, width, height };
    SDL_Rect srcRect = { 0, 0, this->srcRect.w, this->srcRect.h };

    if (texture) {
        SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, nullptr, SDL_FLIP_NONE);
    } else {
        std::cerr << "Texture is invalid or not loaded." << std::endl;
    }
}


