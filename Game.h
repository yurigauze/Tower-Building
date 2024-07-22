#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <list>
#include "box2d/box2d.h"
#include <SDL2/SDL.h>
#include "Render/EventHandler.h"
#include "Render/Renderer.h"
#include "Blocks/Block.h"  // Certifique-se de que o caminho está correto
#include "Blocks/BaseBlock.h"
#include "Hook/Hook.h"
#include "Hook/Line.h"
#include "Constants.h"
#include "DebugDraw.h"

class Game {
public:
    Game(const char* title, int xpos, int ypos, int width, int height, bool fullscreen, Renderer* renderer, EventHandler* eventHandler);

    void addBlock(b2Vec2 anchorPosition);    
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() const { return isRunning; }

private:
    Renderer* renderer;
    BaseBlock* baseBlock;
    EventHandler* eventHandler;
    std::list<Block*> blocks;  // Lista de ponteiros para Block
    b2World* world_;
    Block* block_;
    Hook* hook_;
    Line* line_;
    DebugDraw* debugDraw;
    bool isRunning;
};

#endif // GAME_H
