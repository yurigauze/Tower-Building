#ifndef InitialGame_H
#define InitialGame_H

#include "../sprites/Sprites.h"
#include "../sprites/ClickableSprite.h"
#include "../SDLRenderer.h"
#include "../Camera.h"
#include "../../utils/Utils.h"

#include <SDL2/SDL.h>
#include <string>


class InitialGame
{
public:
    InitialGame(PortRender *renderer, const std::string &textureId,
                    const std::string &texturePath, Camera *camera);
    ~InitialGame();

    ClickableSprite* getButtonnewGame() { return buttonNewGame; }
    ClickableSprite* getButtonexitGame() { return buttonExitGame; }
    ClickableSprite* getButtoncreditsGame() { return buttonCreditsGame; }



    void render(int screenWidth, int screenHeight, int offsetY = 0);



private:

    PortRender *renderer;
    Sprites *InitialGameSprite;
    ClickableSprite *buttonCreditsGame;
    ClickableSprite *buttonNewGame;
    ClickableSprite *buttonExitGame;
    Camera *camera;
    int renderY;

};

#endif // InitialGame_H
