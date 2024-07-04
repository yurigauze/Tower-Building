#include "Game.h"
#include "Blocks/Block.h"
#include "Blocks/BaseBlock.h"
#include "Hook/Hook.h"
#include "Constants.h"
#include <list>

std::list<Block> blocks;
Hook* hook_;

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen){

    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        renderer = SDL_CreateRenderer(window, -1, 0);
        
        b2Vec2 gravity(0.0f, 3.0f);
        world_ = new b2World(gravity);
        
        blocks.push_back(BaseBlock(world_, 300.0f, 600.0f, 141.0f, 100.0f, 255, 255, 0));
        hook_ = new Hook(world_, 315.0f, 100.0f, HOOK_X, HOOK_Y);
        blocks.push_back(Block(world_, 300.0f, 200.0f, 141.0f, 100.0f,255, 0, 0));

        isRunning = true;

    } else {
        isRunning = false;
    }
}

void Game::handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                 
                break;

            default:
                break;
        }
    }
}


void Game::update(){

    world_->Step(1.0f/60.0f, 8, 3);

}

void Game::render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);
    
    for (auto it = blocks.begin(); it != blocks.end(); ++it) {
        it->render(renderer);
    }
    hook_->render(renderer);
    SDL_RenderPresent(renderer);
}


void Game::clean(){
    delete world_;
    delete hook_;
    SDL_DestroyWindow(window);  
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
 
}