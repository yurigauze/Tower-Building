#include "Game.h"
#include <list>

std::list<Block*> blocks;
Hook* hook_;
Line* line_;

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Renderer* renderer, EventHandler* eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true){
        
        b2Vec2 gravity(0.0f, 1.81f);
        
        world_ = new b2World(gravity);

        debugDraw = new DebugDraw(renderer);
        world_->SetDebugDraw(debugDraw);

        uint32 flags = 0;
        flags = b2Draw::e_shapeBit;
        debugDraw->SetFlags(flags);
        
        baseBlock = new BaseBlock(world_);
        hook_ = new Hook(world_);
        line_ = new Line(world_);
        blocks.push_back(new Block(world_));

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

    float deltaTime = 1.0f / 60.0f; 
    world_->Step(deltaTime, 8, 3);
}

void Game::render() {
    renderer->setDrawColor(0, 0, 0, 255);
    renderer->clear();

    world_->DebugDraw();
    
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
    delete line_;

    for (auto block : blocks) {
       delete block;
    }
    blocks.clear();
 
}