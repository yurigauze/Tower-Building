#include "Sprites.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Sprites::Sprites(const std::string &id, const std::string &filePath,
                 PortRender *renderer, int frameWidth, int frameHeight,
                 int totalFrames, float frameTime)
    : id(id), frameWidth(frameWidth), frameHeight(frameHeight), currentFrame(0),
      totalFrames(totalFrames), frameTime(frameTime), currentFrameTime(0.0f),
      renderer(renderer)
{
  bool loadSuccess = renderer->loadTexture(id, filePath);
  if (loadSuccess)
  {
    texture = renderer->getTexture(id);

    if (frameWidth <= 0 || frameHeight <= 0)
    {
      SDL_QueryTexture(texture, NULL, NULL, &srcRect.w, &srcRect.h);
      frameWidth = srcRect.w / totalFrames;
      frameHeight = srcRect.h;
    }
    else
    {
      srcRect = {0, 0, frameWidth, frameHeight};
    }
    destRect = {0, 0, frameWidth, frameHeight};
  }
  else
  {
    texture = nullptr;
    std::cerr << "Erro ao carregar textura: " << filePath << std::endl;
  }
}

Sprites::~Sprites()
{
  if (texture)
  {
    renderer->destroyTexture(texture); 
  }
}
void Sprites::update(float deltaTime)
{
  if (texture)
  {
    currentFrameTime += deltaTime;

    if (currentFrameTime >= frameTime)
    {
      currentFrameTime = 0.0f;
      ++currentFrame;


      if (currentFrame >= totalFrames)
      {
        currentFrame = totalFrames - 1; 

      }

      srcRect.x = currentFrame * frameWidth; 
      srcRect.y = 0;                         
      srcRect.w = frameWidth;
      srcRect.h = frameHeight;

    }
  }
}

void Sprites::render(SDL_Renderer *renderer, int x, int y, int width,
                     int height)
{
  if (texture)
  {
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;

    if (SDL_RenderCopy(renderer, texture, &srcRect, &destRect) != 0)
    {
      std::cerr << "SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
    }
  }
  else
  {
    std::cerr << "Texture not loaded!" << std::endl;
  }
}

void Sprites::renderFullImage(SDL_Renderer *renderer, int x, int y, int width,
                              int height)
{
  if (texture)
  {
    SDL_Rect fullRect = {0, 0, srcRect.w,
                         srcRect.h};
    destRect.x = x;
    destRect.y = y;
    destRect.w = width;
    destRect.h = height;
    if (SDL_RenderCopy(renderer, texture, &fullRect, &destRect) != 0) {
    std::cerr << "SDL_RenderCopy failed: " << SDL_GetError() << std::endl;
}

  }
  else
  {
    std::cerr << "Texto não carregado" << std::endl;
  }
}

void Sprites::renderWithRotation(SDL_Renderer *renderer, int x, int y,
                                 int width, int height, double angle)
{
  if (texture)
  {
    SDL_Rect destRect = {x, y, width, height};
    SDL_RenderCopyEx(renderer, texture, &srcRect, &destRect, angle, nullptr,
                     SDL_FLIP_NONE);
  }
  else
  {
    std::cerr << "Texture is invalid or not loaded." << std::endl;
  }
}
bool Sprites::isLastFrame() const { return currentFrame == totalFrames - 1; }

void Sprites::reset()
{
  currentFrame = 0;        // Volta para o primeiro frame
  currentFrameTime = 0.0f; // Zera o tempo de frame atual
}