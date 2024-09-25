#include "Sprites.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Sprites::Sprites(const std::string &id, const std::string &filePath,
                 PortRender *renderer, int frameWidth, int frameHeight,
                 int totalFrames, float frameTime)
    : id(id), frameWidth(frameWidth), frameHeight(frameHeight), currentFrame(0),
      totalFrames(totalFrames), frameTime(frameTime), currentFrameTime(0.0f),
      renderer(renderer) {
  bool loadSuccess = renderer->loadTexture(id, filePath);
  if (loadSuccess) {
    texture = renderer->getTexture(id);

    if (frameWidth <= 0 || frameHeight <= 0) {
      // Ajusta srcRect para cobrir a imagem inteira
      SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
      frameWidth = srcRect.w / totalFrames; // Calcula a largura de cada frame
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
    renderer->destroyTexture(texture); // Destrói a textura, se necessário
  }
}
void Sprites::update(float deltaTime) {
  if (texture) {
    currentFrameTime += deltaTime;
    if (currentFrameTime >= frameTime) {
      currentFrameTime = 0.0f;
      ++currentFrame;
      if (currentFrame >= totalFrames) {
        currentFrame = totalFrames - 1; // Para no último frame
        // Se desejar reiniciar a animação, descomente a linha abaixo
        // currentFrame = 0;
      }
    }
  }
}

void Sprites::render(SDL_Renderer *renderer, int x, int y, int width,
                     int height) {
  if (texture) {
    // Configura a posição e o tamanho da imagem a ser desenhada na tela
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    std::cout << "Rendering sprite frame at position (" << x << ", " << y
              << ") with size (" << width << ", " << height << ")"
              << " using source rect (" << srcRect.x << ", " << srcRect.y
              << ", " << srcRect.w << ", " << srcRect.h << ")." << std::endl;

    // Desenha o frame atual da spritesheet na tela
    if (SDL_RenderCopy(renderer, texture, &srcRect, &destRect) != 0) {
      std::cerr << "SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
    }
  } else {
    std::cerr << "Texture not loaded!" << std::endl;
  }
}

void Sprites::renderFullImage(SDL_Renderer *renderer, int x, int y, int width,
                              int height) {
  if (texture) {
    SDL_Rect fullRect = {0, 0, srcRect.w,
                         srcRect.h}; // srcRect cobre a textura inteira
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
    SDL_RenderCopy(renderer, texture, &fullRect, &destRect);
  } else {
    std::cerr << "Texto não carregado" << std::endl;
  }
}

void Sprites::renderWithRotation(SDL_Renderer *renderer, int x, int y,
                                 int width, int height, double angle) {
  if (texture) {
    SDL_Rect destRect = {x, y, width, height};
    // srcRect já está definido corretamente
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, nullptr,
                     SDL_FLIP_NONE);
  } else {
    std::cerr << "Texture is invalid or not loaded." << std::endl;
  }
}
bool Sprites::isLastFrame() const { return currentFrame == totalFrames - 1; }

void Sprites::reset() {
  currentFrame = 0;        // Volta para o primeiro frame
  currentFrameTime = 0.0f; // Zera o tempo de frame atual
}