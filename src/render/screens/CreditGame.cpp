#include "CreditGame.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <fstream>

CreditGame::CreditGame(PortRender *renderer, const std::string &textureId,
                       const std::string &texturePath, Camera *camera)
    : renderer(renderer), CreditGameSprite(nullptr), camera(camera), renderY(0)
{
    if (renderer)
    {
        CreditGameSprite = new Sprites(textureId, texturePath, renderer);
        buttonExitGame = new ClickableSprite("ExitGame", "assets/Exit.png", renderer);

        if (CreditGameSprite && CreditGameSprite->getTexture())
        {
            std::cout << "CreditGameSprite inicializado com sucesso!" << std::endl;
        }
        else
        {
            std::cerr << "Erro ao inicializar CreditGameSprite!" << std::endl;
            delete CreditGameSprite;
            CreditGameSprite = nullptr;
        }
    }
    else
    {
        std::cerr << "Erro: O renderer não está inicializado!" << std::endl;
    }
}

CreditGame::~CreditGame()
{
    delete CreditGameSprite;
    delete buttonExitGame;
}

void CreditGame::render(int screenWidth, int screenHeight, int offsetY)
{
    if (CreditGameSprite)
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

        CreditGameSprite->renderFullImage(sdlRenderer->getRenderer(), 0, offsetY, newWidth, newHeight);
        sdlRenderer->drawText("Tower Building", 100, 100, 0, 0, 0, 255);
        sdlRenderer->drawText("Desenvolvido nas materias de:", 100, 120, 0, 0, 0, 255);
        sdlRenderer->drawText("Tópicos em Computação: Professor Eduardo", 100, 140, 0, 0, 0, 255);
        sdlRenderer->drawText("Projeto de Software Avançado : Professro Helio", 100, 160, 0, 0, 0, 255);
        buttonExitGame->renderFullImage(sdlRenderer->getRenderer(), 200, 300, 210, 70);
    }
    else
    {
        std::cerr << "Erro: CreditGameSprite não está inicializado!" << std::endl;
    }
}
