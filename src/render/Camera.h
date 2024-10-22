#include <SDL2/SDL.h>

#ifndef CAMERA_H
#define CAMERA_H

class Camera
{
public:
    SDL_Rect viewport;
    int worldHeight;
    Camera(int viewportWidth, int viewportHeight, int worldHeight)
        : worldHeight(worldHeight)
    {
        viewport = {0, 0, viewportWidth, viewportHeight};
    }

    void moveY(int dy)
    {
        viewport.y += dy;
    }
    SDL_Rect getView() const
    {
        return viewport;
    }
};

#endif // CAMERA_H