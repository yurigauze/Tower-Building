#include "utils/Utils.h"
#include "include/box2d/box2d.h"
#include "Game.h"
#include "utils/Constants.h"
#include "render/SDLImplements.h"
#include "render/audio/AudioManager.h"

Game* game = nullptr; 

int main(int argc, char* argv[]) {

    try {
        SDLImplements sdlImplements("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false);

        if (!AudioManager::getInstance().init()) {
            return -1;
        }

        AudioManager::getInstance().loadSoundEffect("block_drop", "assets/sounds/drop.ogg");
        AudioManager::getInstance().loadMusic("assets/sounds/bgm.ogg");

        AudioManager::getInstance().playMusic();

        game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false, sdlImplements.getRenderer(), sdlImplements.getEventHandler());

        while (game->running()) {
            game->handleEvents();
            game->update();
            game->render();

        }

        delete game;
        AudioManager::getInstance().cleanUp();

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;
}
