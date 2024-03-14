#include "Game.h"
#include "Blocos/Bloco.h"

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){
    int flags = 0;
    if (fullscreen){
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0){
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        renderer = SDL_CreateRenderer(window, -1, 0);


        b2Vec2 gravity(0.0f, 9.8f);
        world_ = new b2World(gravity);

        // Adicione alguns blocos ao jogo
        for (int i = 0; i < 5; ++i) {
            Bloco.push_back(Bloco(world_, 50, 50, 1.0f, 0.5f, 0.2f, b2Vec2(100 + i * 100, 100), 255, 0, 0));
        }

        isRunning = true;

    } else {
        isRunning = false;
    }

};

void Game::handleEvents(){
    SDL_Event event;
    SDL_PollEvent(&event);
    switch (event.type){
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
        break;
    }
}

void Game::update(){

}

void Game::render(){
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    for (const auto& bloco : blocos) {
        bloco.renderizar(renderer);
    }

    SDL_RenderPresent(renderer);
}

void Game::clean(){
    delete world_;
    SDL_DestroyWindow(window);  
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
 
}