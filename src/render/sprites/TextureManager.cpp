#include "TextureManager.h"
#include "../SDLRenderer.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <stdexcept>

TextureManager::TextureManager(PortRender *renderer) : renderer(renderer) {}

TextureManager::~TextureManager() {
  for (auto &pair : textures) {
    SDL_DestroyTexture(pair.second);
  }
}

bool TextureManager::loadTexture(const std::string &id,
                                 const std::string &filename) {
  SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
  if (!sdlRenderer) {
    std::cerr << "Failed to get SDLRenderer instance." << std::endl;
    return false;
  }

  SDL_Renderer *sdlRendererPtr = sdlRenderer->getRenderer();
  if (!sdlRendererPtr) {
    std::cerr << "Failed to get SDL_Renderer." << std::endl;
    return false;
  }

  SDL_Surface *surface = IMG_Load(filename.c_str());
  if (!surface) {
    std::cerr << "Failed to load image: " << IMG_GetError() << std::endl;
    return false;
  }

  SDL_Texture *texture = SDL_CreateTextureFromSurface(sdlRendererPtr, surface);
  SDL_FreeSurface(surface);

  if (!texture) {
    std::cerr << "Failed to create texture: " << SDL_GetError() << std::endl;
    return false;
  }

  textures[id] = texture; // Usa 'textures' para armazenar a textura
  std::cout << "Texture loaded with ID: " << id << std::endl;
  return true;
}

void TextureManager::drawTexture(const std::string &id, float x, float y,
                                 SDL_Rect *srcRect) {
  auto it = textures.find(id);
  if (it == textures.end()) {
    std::cerr << "Texture with ID " << id << " not found." << std::endl;
    return;
  }

  SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
  if (!sdlRenderer) {
    std::cerr << "Failed to get SDLRenderer instance." << std::endl;
    return;
  }

  SDL_Renderer *sdlRendererPtr = sdlRenderer->getRenderer();
  if (!sdlRendererPtr) {
    std::cerr << "Failed to get SDL_Renderer." << std::endl;
    return;
  }

  // Converta as coordenadas para inteiros
  SDL_Rect dstRect;
  dstRect.x = static_cast<int>(x);
  dstRect.y = static_cast<int>(y);

  if (srcRect) {
    dstRect.w = srcRect->w;
    dstRect.h = srcRect->h;
  } else {
    // Se srcRect for nullptr, você precisa obter as dimensões da textura.
    SDL_Texture *texture = it->second;
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    dstRect.w = textureWidth;
    dstRect.h = textureHeight;
  }

  if (SDL_RenderCopy(sdlRendererPtr, it->second, srcRect, &dstRect) != 0) {
    std::cerr << "Failed to render texture: " << SDL_GetError() << std::endl;
  }
}

void TextureManager::rotation(const std::string &id, float angle) {
    auto it = textures.find(id);
    if (it == textures.end()) {
        std::cerr << "Texture with ID " << id << " not found." << std::endl;
        return;
    }

    SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
    if (!sdlRenderer) {
        std::cerr << "Failed to get SDLRenderer instance." << std::endl;
        return;
    }

    SDL_Renderer *sdlRendererPtr = sdlRenderer->getRenderer();
    if (!sdlRendererPtr) {
        std::cerr << "Failed to get SDL_Renderer." << std::endl;
        return;
    }

    SDL_Texture *originalTexture = it->second;

  
    int textureWidth, textureHeight;
    SDL_QueryTexture(originalTexture, NULL, NULL, &textureWidth, &textureHeight);
    SDL_Texture *target = SDL_CreateTexture(sdlRendererPtr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, textureWidth, textureHeight);
    if (!target) {
        std::cerr << "Failed to create target texture: " << SDL_GetError() << std::endl;
        return;
    }

    SDL_SetRenderTarget(sdlRendererPtr, target);

    SDL_SetRenderDrawColor(sdlRendererPtr, 0, 0, 0, 255);
    SDL_RenderClear(sdlRendererPtr);

    SDL_RenderCopyEx(sdlRendererPtr, originalTexture, NULL, NULL, angle, NULL, SDL_FLIP_NONE);

    SDL_SetRenderTarget(sdlRendererPtr, NULL);


    SDL_DestroyTexture(originalTexture);
    textures[id] = target;
}
