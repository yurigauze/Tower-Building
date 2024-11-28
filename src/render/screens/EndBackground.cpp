#include "EndBackground.h"
#include <iostream>

EndBackground::EndBackground(PortRender *renderer, const std::string &textureId,
                                   const std::string &texturePath, Camera *camera)
    : renderer(renderer), endBackgroundSprite(nullptr), camera(camera), renderY(0)
{
    if (renderer)
    {
        endBackgroundSprite = new Sprites(textureId, texturePath, renderer);
        if (endBackgroundSprite && endBackgroundSprite->getTexture())
        {
            std::cout << "endBackgroundSprite inicializado com sucesso!" << std::endl;
        }
        else
        {
            std::cerr << "Erro ao inicializar endBackgroundSprite!" << std::endl;
            delete endBackgroundSprite;
            endBackgroundSprite = nullptr;
        }
    }
    else
    {
        std::cerr << "Erro: O renderer não está inicializado!" << std::endl;
    }
}

EndBackground::~EndBackground()
{
    delete endBackgroundSprite;

}

void EndBackground::render(int screenWidth, int screenHeight, int offsetY)
{
    if (endBackgroundSprite)
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

        endBackgroundSprite->renderFullImage(sdlRenderer->getRenderer(), 0, offsetY, newWidth, newHeight);
        
    }
    else
    {
        std::cerr << "Erro: endBackgroundSprite não está inicializado!" << std::endl;
    }
}
