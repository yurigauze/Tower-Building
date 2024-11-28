#ifndef ENDBACKGROUND_H
#define ENDBACKGROUND_H

#include "../sprites/Sprites.h"
#include "../sprites/ClickableSprite.h"
#include "../SDLRenderer.h"
#include "../Camera.h"
#include "../../utils/Utils.h"

#include <SDL2/SDL.h>
#include <string>

class EndBackground
{
public:
    EndBackground(PortRender *renderer, const std::string &textureId,
                    const std::string &texturePath, Camera *camera);
    ~EndBackground();

    void render(int screenWidth, int screenHeight, int offsetY = 0);

private:
    PortRender *renderer;
    Sprites *endBackgroundSprite;
    Camera *camera;
    int renderY;
};

#endif // ENDBACKGROUND_H
