
#include "src/utils/Utils.h"
#include "src/include/box2d/box2d.h"
#include "Game.h"
#include "src/utils/Constants.h"
#include "src/render/SDLImplements.h"


Game* game = nullptr; 

int main(int argc, char* argv[]) {

    try {
        SDLImplements sdlImplements("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false);

        game = new Game("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false, sdlImplements.getRenderer(), sdlImplements.getEventHandler());

        while (game->running()) {
            game->handleEvents();
            game->update();
            game->render();
            
        }
    
        delete game;

    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
        return -1;
    }

    return 0;

}
