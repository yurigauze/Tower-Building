#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "../models/Block.h"
#include "../models/BlockTest.h"
#include <SDL2/SDL.h>
#include <list>
#include "../render/EventHandler.h"
#include "../render/PortRender.h" 
#include "../render/camera/Camera.h" 
#include "../models/rules/BlockManager.h"

class BlockManager;

class Controller {
public:
    Controller(EventHandler* eventHandler, b2World* world, Block*& block, std::list<Block*>& gameBlocks, bool& isRunning, PortRender* renderer,  BlockTest* blockTest, Camera *camera, BlockManager *blockManager, bool &isBlockOnHookActive);
    void handleEvents();
    void addBlockIfPositioned(Block* newBlock);

private:
    EventHandler* eventHandler_;
    b2World* world_;
    Block*& block_;
    std::list<Block*>& gameBlocks_;
    bool& isRunning_;
    PortRender* renderer_;
    BlockTest* blockTest;
    Camera *camera;
    BlockManager *blockManager_;
    bool &isBlockOnHookActive;
    

    static const int AnchorPositionX = 300;
    static const int AnchorPositionY = -20;
};

#endif // CONTROLLER_H
