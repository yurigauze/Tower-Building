// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include "../utils/Utils.h"
#include <SDL2/SDL.h>
#include <string>

class PortRender {
public:
  virtual ~PortRender() = default;
  virtual void clear() = 0;
  virtual void setDrawColor(int r, int g, int b, int a) = 0;
  virtual void drawRect(int x, int y, int w, int h) = 0;
  virtual void present() = 0;
  virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
  virtual void drawCircle(int x, int y, int radius) = 0;
  virtual void drawPoint(int x, int y) = 0;

  virtual bool loadFont(const std ::string &path, int size) { return false; }
  virtual void drawText(const std::string &text, int x, int y, int r, int g,
                        int b, int a) = 0;

  virtual bool loadTexture(const std::string &id,
                           const std::string &filename) = 0;
  virtual void drawTexture(const std::string &id, int x, int y,
                           SDL_Rect *srcRect = nullptr) = 0;

  virtual SDL_Renderer *getRenderer() const { return nullptr; }
};

#endif // RENDERER_H
