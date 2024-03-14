#include <SDL2/SDL.h>
#include <list>
#include "Blocos/Bloco.h"
#include "Blocos/BlocoBase.h"
#include "Constants.h"
#include "Utils/Utils.h"
#include "box2d/box2d.h"
#include "Game.h"


Game* game = nullptr;

int main(int argc, char* argv[]) {
    game = new Game("Tower Building", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, LARGURA, ALTURA, false);
    
    const Uint8* keys = SDL_GetKeyboardState(NULL);

    while(game->running())
    {   
        game->render();
		game->handleEvents();
		SDL_RenderPresent(game->renderer);


    }

    game->clean();
    delete game;

    return 0;

}
