#include "Game.h"
#include <list>


Hook* hook_;
Line* line_;

Game::Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Renderer* renderer, EventHandler* eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true){
        
        b2Vec2 gravity(0.0f, 9.81f);
        
        world_ = new b2World(gravity);

        debugDraw = new DebugDraw(renderer);
        world_->SetDebugDraw(debugDraw);

        uint32 flags = 0;
        flags |= b2Draw::e_shapeBit;
        debugDraw->SetFlags(flags);

        b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
        hook_ = new Hook(world_, anchorPosition);

        block_ = new Block(world_);
        
        baseBlock = new BaseBlock(world_);
        

        //line_ = new Line(world_);

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

    static float time = 0.0f;
    float deltaTime = 1.0f / 120.0f; 
    time += deltaTime;

    hook_->applyInitialForce(time);
    world_->Step(deltaTime, 8, 3);
    
}

void Game::render() {

    renderer->setDrawColor(0, 0, 0, 255);
    renderer->clear();

    world_->DebugDraw();

    hook_->render(renderer);
    //line_->render(renderer);
    renderer->present();
    
}


void Game::clean(){
    delete world_;
    delete debugDraw;
    delete hook_;
    //delete line_;
 
}