#ifndef PAUSEBACKGROUND_H
#define PAUSEBACKGROUND_H

#include "../../render/sprites/Sprites.h"
#include "../../render/sprites/ClickableSprite.h"
#include "../../render/SDLRenderer.h"
#include "../../render/Camera.h"
#include "../../utils/Utils.h"

#include <SDL2/SDL.h>
#include <string>

class PauseBackground
{
public:
    PauseBackground(PortRender *renderer, const std::string &textureId,
                    const std::string &texturePath, Camera *camera);
    ~PauseBackground();

    void render(int screenWidth, int screenHeight, int offsetY = 0);

    ClickableSprite* getButtonNG() { return buttonNG; }
    ClickableSprite* getButtonContinue() { return buttonContinue; }

private:
    PortRender *renderer;
    Sprites *pauseBackgroundSprite;
    ClickableSprite *buttonNG;
    ClickableSprite *buttonContinue;
    Camera *camera;
    int renderY;
};

#endif // PAUSEBACKGROUND_H
