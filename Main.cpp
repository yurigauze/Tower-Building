#include <SDL2/SDL.h>
#include <list>
#include "Blocks/Block.h"
#include "Blocks/BaseBlock.h"
#include "Constants.h"
#include "Utils/Utils.h"
#include "box2d/box2d.h"
#include "Game.h"


Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game("Tower Building", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, HEIGHT, WIDTH, false);
    
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while(game->running())
    {   
        game->render();
		game->handleEvents();
        game->update();
		SDL_RenderPresent(game->renderer);


    }

    game->clean();
    delete game;

    return 0;

}
