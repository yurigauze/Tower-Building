#include <SDL2/SDL.h>

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    SDL_Rect viewport;
    int worldHeight;
    int initialViewportY;

    Camera(int viewportWidth, int viewportHeight, int worldHeight)
        : worldHeight(worldHeight)
    {
        viewport = {0, 0, viewportWidth, viewportHeight};
        initialViewportY = viewport.y; 
    }

    void moveY(int dy)
    {
        viewport.y += dy;
    }
    SDL_Rect getView() const
    {
        return viewport;
    }

    void reset()
    {
        viewport.y = initialViewportY;
    }
};

#endif // CAMERA_H