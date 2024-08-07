// Renderer.h
#ifndef RENDERER_H
#define RENDERER_H

#include <string>
#include <SDL2/SDL.h> 

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

};

#endif // RENDERER_H
