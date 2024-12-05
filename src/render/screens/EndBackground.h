#ifndef ENDBACKGROUND_H
#define ENDBACKGROUND_H

#include "../sprites/Sprites.h"
#include "../sprites/ClickableSprite.h"
#include "../SDLRenderer.h"
#include "../Camera.h"
#include "../../utils/Utils.h"

#include <SDL2/SDL.h>
#include <string>

class BlockManager;

class EndBackground
{
public:
    EndBackground(PortRender *renderer, const std::string &textureId,
                    const std::string &texturePath, Camera *camera, BlockManager *BlockManager);
    ~EndBackground();

    ClickableSprite* getButtonnewGame() { return buttonNewGame; }

    void render(int screenWidth, int screenHeight, int offsetY = 0);

    void handleKeyboardEvent(SDL_Event &e);

    void saveScore(const std::string &playerName);
    void renderUserInput(SDLRenderer *sdlRenderer);


private:

    PortRender *renderer;
    Sprites *endBackgroundSprite;
    Sprites *gameOver;
    ClickableSprite *buttonNewGame;
    Camera *camera;
    BlockManager *blockManager;
    int renderY;

    std::string userInput;
};

#endif // ENDBACKGROUND_H
