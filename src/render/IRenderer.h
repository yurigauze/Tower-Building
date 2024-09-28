// IRenderer.h
#ifndef IRENDERER_H
#define IRENDERER_H

#include <SDL.h>

class IRenderer {
public:
    virtual ~IRenderer() = default;

    virtual void clear() = 0;
    virtual void setDrawColor(int r, int g, int b, int a) = 0;
    virtual void drawRect(int x, int y, int width, int height) = 0;
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
    virtual void drawCircle(int x, int y, int radius) = 0;
    virtual void drawPoint(int x, int y) = 0;
    virtual void present() = 0;
    virtual bool loadTexture(const std::string &id, const std::string &filePath) = 0;
    virtual SDL_Texture* getTexture(const std::string& id) = 0;
    virtual void drawTexture(const std::string &id, int x, int y, SDL_Rect *srcRect) = 0;
    virtual void destroyTexture(SDL_Texture* texture) = 0;
    virtual bool loadFont(const std::string &path, int size) = 0;
    virtual void drawText(const std::string &text, int x, int y, int r, int g, int b, int a) = 0;
};

#endif // IRENDERER_H
