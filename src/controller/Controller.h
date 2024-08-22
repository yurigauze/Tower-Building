#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../models/Block.h"
#include <SDL2/SDL.h>
#include <list>
#include "../render/EventHandler.h"

class Controller {
public:
    Controller(EventHandler* eventHandler, b2World* world, Block*& block, std::list<Block*>& gameBlocks, bool& isRunning);
    void handleEvents();

private:
    EventHandler* eventHandler_;
    b2World* world_;
    Block*& block_;
    std::list<Block*>& gameBlocks_;
    bool& isRunning_;

    static const int AnchorPositionX = 300;
    static const int AnchorPositionY = -20;
};

#endif // CONTROLLER_H
