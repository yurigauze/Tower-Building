#include <SDL2/SDL.h>

#ifndef CAMERA_H
#define CAMERA_H

class Camera {
public:
    SDL_Rect viewport;
    int worldHeight;   

    Camera(int viewportWidth, int viewportHeight, int worldHeight) 
        : worldHeight(worldHeight) 
    {
        viewport = { 0, 0, viewportWidth, viewportHeight }; // X é sempre 0
    }

    // Move a câmera apenas no eixo Y
    void moveY(int dy) {
        viewport.y += dy;

    }

    SDL_Rect getView() const {
        return viewport;
    }
};

#endif // CAMERA_H