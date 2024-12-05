#include "utils/Utils.h"
#include "include/box2d/box2d.h"
#include "Game.h"
#include "utils/Constants.h"
#include "render/SDLImplements.h"
#include "render/audio/AudioManager.h"

Game *game = nullptr;

int main(int argc, char *argv[])
{
    try
    {
        SDLImplements sdlImplements("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false);

        if (!AudioManager::getInstance().init())
        {
            return -1;
        }

        // Carregar músicas com IDs distintos
        AudioManager::getInstance().loadMusic("bgm", "assets/sounds/bgm.ogg");
        AudioManager::getInstance().loadMusic("gameover", "assets/sounds/game-over.ogg");
        AudioManager::getInstance().loadSoundEffect("block_drop", "assets/sounds/drop.ogg");
        AudioManager::getInstance().loadSoundEffect("destroy", "assets/sounds/rotate.ogg");

        // Tocar a música de fundo
        AudioManager::getInstance().playMusic("bgm");

        game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false, sdlImplements.getRenderer(), sdlImplements.getEventHandler());

        bool gameOverMusicPlayed = false;

        while (game->running())
        {
            game->handleEvents(); // Captura eventos (incluindo teclado)

            // Checar se o jogo acabou
            if (game->isGameOver())
            {
                if (!gameOverMusicPlayed)
                {
                    AudioManager::getInstance().pauseMusic();
                    AudioManager::getInstance().playMusic("gameover");
                    gameOverMusicPlayed = true;
                }

                game->renderEndgameScreen();
            }
            else if (!game->isPaused())
            {
                game->update();
                game->render();
            }
            else
            {
                game->renderPauseScreen();
            }
        }

        delete game;
        AudioManager::getInstance().cleanUp();
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}