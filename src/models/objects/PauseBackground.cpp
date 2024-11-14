#include "PauseBackground.h"
#include <iostream>

PauseBackground::PauseBackground(PortRender *renderer, const std::string &textureId,
                                   const std::string &texturePath, Camera *camera)
    : renderer(renderer), pauseBackgroundSprite(nullptr), camera(camera), renderY(0)
{
    if (renderer)
    {
        pauseBackgroundSprite = new Sprites(textureId, texturePath, renderer);
        if (pauseBackgroundSprite && pauseBackgroundSprite->getTexture())
        {
            std::cout << "pauseBackgroundSprite inicializado com sucesso!" << std::endl;
        }
        else
        {
            std::cerr << "Erro ao inicializar pauseBackgroundSprite!" << std::endl;
            delete pauseBackgroundSprite;
            pauseBackgroundSprite = nullptr;
        }
    }
    else
    {
        std::cerr << "Erro: O renderer não está inicializado!" << std::endl;
    }

    buttonNG = new ClickableSprite("NewGame", "assets/NewGame.png", renderer);
    buttonContinue = new ClickableSprite("Continue", "assets/Continue.png", renderer);
}

PauseBackground::~PauseBackground()
{
    delete pauseBackgroundSprite;
    delete buttonNG;
    delete buttonContinue;
}

void PauseBackground::render(int screenWidth, int screenHeight, int offsetY)
{
    if (pauseBackgroundSprite)
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

        pauseBackgroundSprite->renderFullImage(sdlRenderer->getRenderer(), 0, offsetY, newWidth, newHeight);
        buttonNG->renderFullImage(sdlRenderer->getRenderer(), 200, 300, 210, 70);
        buttonContinue->renderFullImage(sdlRenderer->getRenderer(), 200, 380, 210, 70);
    }
    else
    {
        std::cerr << "Erro: pauseBackgroundSprite não está inicializado!" << std::endl;
    }
}
