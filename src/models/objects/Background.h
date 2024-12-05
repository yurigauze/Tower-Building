#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "../../render/sprites/Sprites.h"
#include "../../render/SDLRenderer.h"
#include "../../render/Camera.h"
#include "../../utils/Utils.h"

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>

class Background
{
public:
    Background(PortRender *renderer, const std::string &textureId,
               const std::string &texturePath, Camera *camera)
        : renderer(renderer), backgroundSprite(nullptr), camera(camera), renderY(130)
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

        renderGradient(screenWidth, screenHeight, offsetY);

        if (backgroundSprite)
        {

            int adjustedRenderY = renderY - camera->getView().y;

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

            backgroundSprite->renderFullImage(sdlRenderer->getRenderer(), 0, adjustedRenderY + offsetY, newWidth, newHeight);
        }
        else
        {
            std::cerr << "Erro: backgroundSprite não está inicializado!" << std::endl;
        }
    }

    Color getLinearGradientColorRgb(const std::vector<Color> &colors, int colorIndex, float proportion)
    {
        int currentIndex = (colorIndex >= static_cast<int>(colors.size()) - 1) ? static_cast<int>(colors.size()) - 1 : colorIndex;
        Color currentColor = colors[currentIndex];
        int nextIndex = (currentIndex >= static_cast<int>(colors.size()) - 1) ? currentIndex : currentIndex + 1;
        Color nextColor = colors[nextIndex];

        Color interpolatedColor;
        interpolatedColor.r = currentColor.r + static_cast<int>((nextColor.r - currentColor.r) * proportion);
        interpolatedColor.g = currentColor.g + static_cast<int>((nextColor.g - currentColor.g) * proportion);
        interpolatedColor.b = currentColor.b + static_cast<int>((nextColor.b - currentColor.b) * proportion);

        return interpolatedColor;
    }

    void renderGradient(int screenWidth, int screenHeight, int offsetY = 0)
    {
        std::vector<Color> colorArr = {
            {200, 255, 150},
            {105, 230, 240},
            {90, 190, 240},
            {85, 100, 190},
            {55, 20, 35},
            {75, 25, 35},
            {25, 0, 10}};

        int offsetHeight = 100 - camera->getView().y + offsetY;
        int colorIndex = offsetHeight / screenHeight;
        float proportion = static_cast<float>(offsetHeight % screenHeight) / screenHeight;

        Color colorBase = getLinearGradientColorRgb(colorArr, colorIndex, proportion);
        Color colorTop = getLinearGradientColorRgb(colorArr, colorIndex + 1, proportion);

        SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
        if (!sdlRenderer)
        {
            std::cerr << "Erro: renderer não é um SDLRenderer!" << std::endl;
            return;
        }

        for (int y = 0; y < screenHeight; ++y)
        {
            float lerpFactor = static_cast<float>(y) / screenHeight;

            Color currentColor;
            currentColor.r = colorBase.r + static_cast<int>((colorTop.r - colorBase.r) * lerpFactor);
            currentColor.g = colorBase.g + static_cast<int>((colorTop.g - colorBase.g) * lerpFactor);
            currentColor.b = colorBase.b + static_cast<int>((colorTop.b - colorBase.b) * lerpFactor);

            sdlRenderer->setDrawColor(currentColor.r, currentColor.g, currentColor.b, 255);

            sdlRenderer->drawLine(0, y + offsetY, screenWidth, y + offsetY);
        }
    }

    void reset()
    {
        renderY = 130;
    }

private:
    PortRender *renderer;
    Sprites *backgroundSprite;
    Camera *camera;
    int renderY;
    Color color;
};

#endif // BACKGROUND_H
