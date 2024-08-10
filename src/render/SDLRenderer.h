#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include "PortRender.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class SDLRenderer : public PortRender {
public:
  SDLRenderer(SDL_Renderer *renderer);
  ~SDLRenderer() override;

  void clear() override;
  void setDrawColor(int r, int g, int b, int a) override;
  void drawRect(int x, int y, int width, int height) override;
  void drawLine(int x1, int y1, int x2, int y2) override;
  void drawCircle(int x, int y, int radius) override;
  void drawPoint(int x, int y) override;
  void present() override;

  bool loadFont(const std::string& path, int size) override;
  void drawText(const std::string& text, int x, int y, SDL_Color color) override;

private:
  SDL_Renderer *renderer;
  TTF_Font *font;
};

#endif // SDLRENDERER_H
