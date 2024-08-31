#ifndef SDLRENDERER_H
#define SDLRENDERER_H

#include "PortRender.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <map>
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

  bool loadFont(const std::string &path, int size) override;
  void drawText(const std::string &text, int x, int y, int r, int g, int b,
                int a) override;

  SDL_Renderer *getRenderer() const override;

  bool loadTexture(const std::string &id, const std::string &filename) override;
  SDL_Texture* getTexture(const std::string& id) override;
  void drawTexture(const std::string &id, int x, int y, SDL_Rect *srcRect) override;


  void destroyTexture(SDL_Texture *texture) override;

private:
  SDL_Renderer *renderer;
  TTF_Font *font;
  std::map<std::string, SDL_Texture *> textures;
};

#endif // SDLRENDERER_H
