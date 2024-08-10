// SDLRenderer.cpp
#include "SDLRenderer.h"
#include <stdexcept>
#include <iostream>
#include <ostream>


SDLRenderer::SDLRenderer(SDL_Renderer *renderer)
    : renderer(renderer), font(nullptr) {}

SDLRenderer::~SDLRenderer() {
  if (font) {
    TTF_CloseFont(font);
  }
}

void SDLRenderer::clear() { SDL_RenderClear(renderer); }

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

void SDLRenderer::present() { SDL_RenderPresent(renderer); }

bool SDLRenderer::loadFont(const std::string &path, int size) {
    font = TTF_OpenFont(path.c_str(), size);
    if (!font) {
        std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
        return false;
    }
    return true;
}

void SDLRenderer::drawText(const std::string &text, int x, int y,
                           SDL_Color color) {
  if (font == nullptr)
    return;
  SDL_Surface *surface = TTF_RenderText_Solid(font, text.c_str(), color);
  if (surface == nullptr)
    return;
  SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, surface);
  if (texture == nullptr) {
    SDL_FreeSurface(surface);
    return;
  }
  SDL_Rect dstRect = {x, y, surface->w, surface->h};
  SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
  SDL_DestroyTexture(texture);
  SDL_FreeSurface(surface);
}
