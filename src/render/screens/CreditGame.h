#ifndef CreditGame_H
#define CreditGame_H

#include "../sprites/Sprites.h"
#include "../sprites/ClickableSprite.h"
#include "../SDLRenderer.h"
#include "../Camera.h"
#include "../../utils/Utils.h"
#include <SDL2/SDL.h>
#include <string>


class CreditGame
{
public:
    CreditGame(PortRender *renderer, const std::string &textureId,
                    const std::string &texturePath, Camera *camera);
    ~CreditGame();

    ClickableSprite* getButtonexitGame() { return buttonExitGame; }

    void render(int screenWidth, int screenHeight, int offsetY = 0);



private:

    PortRender *renderer;
    Sprites *CreditGameSprite;
    ClickableSprite *buttonExitGame;
    Camera *camera;
    int renderY;

};

#endif // CreditGame_H
