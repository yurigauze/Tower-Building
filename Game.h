#ifndef Game_h
#define Game_h
#include <iostream>
#include <list>
#include "box2d/box2d.h"
#include "Render/EventHandler.h"
#include "Render/Renderer.h"
#include "Blocks/Block.h"
#include "Blocks/BaseBlock.h"
#include "Hook/Hook.h"
#include "Hook/Line.h"
#include "Constants.h"
#include "DebugDraw.h" 

class Game{
    public:

        Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Renderer* renderer, EventHandler* eventHandler);
        
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() const { return isRunning; }

    private:
        Renderer* renderer;
        BaseBlock* baseBlock;
        EventHandler* eventHandler;
        b2World* world_;
        std::list<Block*> blocks; 
        Hook* hook_;
        Line* line_;
        DebugDraw* debugDraw;
        bool isRunning;

};
#endif