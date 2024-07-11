#include "Game.h"
#include "Blocks/Block.h"
#include "Blocks/BaseBlock.h"
#include "Hook/Hook.h"
#include "Constants.h"
#include <list>

std::list<Block*> blocks;
Hook* hook_;

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Renderer* renderer, EventHandler* eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true){
        
        b2Vec2 gravity(0.0f, 3.0f);
        world_ = new b2World(gravity);

        debugDraw = new DebugDraw(renderer);
        world_->SetDebugDraw(debugDraw);
        
        baseBlock = new BaseBlock(world_, 315.0f, 600.0f, 255, 255, 255);
        hook_ = new Hook(world_, 315.0f, 100.0f, HOOK_X, HOOK_Y);
        blocks.push_back(new Block(world_, 315.0f, 200.0f, 255, 0, 255));

}

void Game::handleEvents() {
    while (eventHandler->pollEvent()){
        if(eventHandler->isQuitEvent()){
            isRunning = false;
        } else if (eventHandler->isKeyDownEvent()){
                
        }
    }
}


void Game::update(){
    world_->Step(1.0f/60.0f, 8, 3);
}

void Game::render() {
    renderer->setDrawColor(0, 0, 0, 255);
    renderer->clear();
    
    baseBlock->render(renderer);
    for (auto block : blocks) {
        block->render(renderer);
    }

    hook_->render(renderer);
    renderer->present();
}


void Game::clean(){
    delete world_;
    delete debugDraw;
    delete hook_;

    for (auto block : blocks) {
       delete block;
    }
    blocks.clear();
 
}