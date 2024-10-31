#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../../render/sprites/Sprites.h"
#include "../../render/SDLRenderer.h"
#include "../../render/Camera.h"

#include <iostream>

class Background
{
public:
    Background(PortRender *renderer, const std::string &textureId,
               const std::string &texturePath, Camera *camera)
        : renderer(renderer), backgroundSprite(nullptr), camera(camera), renderY(100) // Começa 100 pixels abaixo
    {
        if (renderer)
        {
            backgroundSprite = new Sprites(textureId, texturePath, renderer);
            if (backgroundSprite && backgroundSprite->getTexture())
            {
                std::cout << "backgroundSprite inicializado com sucesso!" << std::endl;
            }
            else
            {
                std::cerr << "Erro ao inicializar backgroundSprite!" << std::endl;
                delete backgroundSprite;
                backgroundSprite = nullptr;
            }
        }
        else
        {
            std::cerr << "Erro: O renderer não está inicializado!" << std::endl;
        }
    }

    ~Background()
    {
        delete backgroundSprite;
    }

    void render(int screenWidth, int screenHeight, int offsetY = 0)
    {
        if (backgroundSprite)
        {

            renderY -= camera->getView().y;


            const int minRenderY = 0; 
            renderY = std::max(renderY, minRenderY);
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

            backgroundSprite->renderFullImage(sdlRenderer->getRenderer(), 0, renderY + offsetY, newWidth, newHeight);
        }
        else
        {
            std::cerr << "Erro: backgroundSprite não está inicializado!" << std::endl;
        }
    }

private:
    PortRender *renderer;
    Sprites *backgroundSprite;
    Camera *camera; 
    int renderY; 
};

#endif // BACKGROUND_H
