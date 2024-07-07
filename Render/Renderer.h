// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

class Renderer {
public:
    virtual ~Renderer() = default;
    virtual void clear() = 0;
    virtual void setDrawColor(int r, int g, int b, int a) = 0;
    virtual void drawRect(int x, int y, int w, int h) = 0;
    virtual void present() = 0;
};

#endif // RENDERER_H
