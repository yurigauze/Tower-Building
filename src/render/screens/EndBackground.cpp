#include "EndBackground.h"
#include "../../models/rules/BlockManager.h"
#include <iostream>
#include <SDL2/SDL_ttf.h>
#include <fstream>

EndBackground::EndBackground(PortRender *renderer, const std::string &textureId,
                             const std::string &texturePath, Camera *camera, BlockManager *blockManager)
    : renderer(renderer), endBackgroundSprite(nullptr), camera(camera), blockManager(blockManager), renderY(0),
      userInput("")
{
    if (renderer)
    {
        endBackgroundSprite = new Sprites(textureId, texturePath, renderer);
        gameOver = new Sprites("gameOver", "assets/GameOver.png", renderer);
        buttonNewGame = new ClickableSprite("NewGame", "assets/NewGame.png", renderer);

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
        gameOver->renderFullImage(sdlRenderer->getRenderer(), 200, 300, 210, 70);
        buttonNewGame->renderFullImage(sdlRenderer->getRenderer(), 200, 380, 210, 70);

        renderUserInput(sdlRenderer);
    }
    else
    {
        std::cerr << "Erro: endBackgroundSprite não está inicializado!" << std::endl;
    }
}

void EndBackground::handleKeyboardEvent(SDL_Event &e)
{
    if (e.type == SDL_KEYDOWN)
    {
        if (e.key.keysym.sym == SDLK_BACKSPACE && userInput.length() > 0)
        {
            userInput.pop_back();
        }
        else if (e.key.keysym.sym == SDLK_RETURN)
        {
            saveScore(userInput);
        }
        else if (e.key.keysym.sym >= SDLK_SPACE && e.key.keysym.sym <= SDLK_z)
        {
            userInput += static_cast<char>(e.key.keysym.sym);
        }
    }
}

void EndBackground::renderUserInput(SDLRenderer *sdlRenderer)
{
    if (userInput.empty())
        return;

    static SDL_Texture *textTexture = nullptr;
    static int textWidth = 0, textHeight = 0;

    if (textTexture)
    {
        SDL_DestroyTexture(textTexture);
    }

    TTF_Font *font = TTF_OpenFont("font/ARIAL.TTF", 24);
    if (font == nullptr)
    {
        std::cerr << "Erro ao carregar fonte!" << std::endl;
        return;
    }

    SDL_Color color = {0, 0, 0};
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, userInput.c_str(), color);
    textTexture = SDL_CreateTextureFromSurface(sdlRenderer->getRenderer(), textSurface);
    SDL_FreeSurface(textSurface);

    SDL_QueryTexture(textTexture, NULL, NULL, &textWidth, &textHeight);
    SDL_Rect renderQuad = {200, 500, textWidth, textHeight};

    SDL_RenderCopy(sdlRenderer->getRenderer(), textTexture, NULL, &renderQuad);
    TTF_CloseFont(font);
}

void EndBackground::saveScore(const std::string &playerName)
{
    std::ofstream file("highscores.txt", std::ios::app);
    if (file.is_open())
    {
        file << playerName << " - " << "Score: " << std::to_string(blockManager->getScore()) << "\n";
        file.close();
        std::cout << "Score salvo com sucesso!" << std::endl;
    }
    else
    {
        std::cerr << "Erro ao salvar o score!" << std::endl;
    }
}