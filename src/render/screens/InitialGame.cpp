#include "InitialGame.h"
#include "../../models/rules/BlockManager.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <fstream>

InitialGame::InitialGame(PortRender *renderer, const std::string &textureId,
                             const std::string &texturePath, Camera *camera)
    : renderer(renderer), InitialGameSprite(nullptr), camera(camera), renderY(0)
{
    if (renderer)
    {
        InitialGameSprite = new Sprites(textureId, texturePath, renderer);
        buttonNewGame = new ClickableSprite("NewGame", "assets/NewGame.png", renderer);
        buttonExitGame = new ClickableSprite("ExitGame", "assets/Exit.png", renderer);
        buttonCreditsGame = new ClickableSprite("Credits", "assets/Credits.png", renderer);


        if (InitialGameSprite && InitialGameSprite->getTexture())
        {
            std::cout << "InitialGameSprite inicializado com sucesso!" << std::endl;
        }
        else
        {
            std::cerr << "Erro ao inicializar InitialGameSprite!" << std::endl;
            delete InitialGameSprite;
            InitialGameSprite = nullptr;
        }
    }
    else
    {
        std::cerr << "Erro: O renderer não está inicializado!" << std::endl;
    }
}

InitialGame::~InitialGame()
{
    delete InitialGameSprite;
    delete buttonExitGame;
}

void InitialGame::render(int screenWidth, int screenHeight, int offsetY)
{
    if (InitialGameSprite)
    {
        SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
        if (!sdlRenderer)
        {
            std::cerr << "Erro: renderer não é um SDLRenderer!" << std::endl;
            return;
        }

        const int originalWidth = 600;
        const int originalHeight = 840;

        float aspectRatio = static_cast<float>(originalWidth) / static_cast<float>(originalHeight);

        int newWidth, newHeight;
        if (screenWidth / aspectRatio <= screenHeight)
        {
            newWidth = screenWidth;
            newHeight = static_cast<int>(screenWidth / aspectRatio);
        }
        else
        {
            newHeight = screenHeight;
            newWidth = static_cast<int>(screenHeight * aspectRatio);
        }

        if (newWidth < screenWidth)
        {
            newWidth = screenWidth;
            newHeight = static_cast<int>(screenWidth / aspectRatio);
        }

        InitialGameSprite->renderFullImage(sdlRenderer->getRenderer(), 0, offsetY, newWidth, newHeight);
        buttonCreditsGame->renderFullImage(sdlRenderer->getRenderer(), 300, 300, 70, 70);
        buttonNewGame->renderFullImage(sdlRenderer->getRenderer(), 200, 380, 210, 70);
        buttonExitGame->renderFullImage(sdlRenderer->getRenderer(), 200, 460, 210, 70); 

    }
    else
    {
        std::cerr << "Erro: InitialGameSprite não está inicializado!" << std::endl;
    }
}
