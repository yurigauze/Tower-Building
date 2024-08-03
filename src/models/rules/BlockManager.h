#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <list>
#include "../Block.h"
#include "../../utils/Utils.h"

class BlockManager {
public:
    BlockManager(b2World* world, std::list<Block*>& blocks, float limit);
    void update(float deltaTime);

private:
    void destroyBlock(Block* block);

    b2World* world_;
    std::list<Block*>& blocks_;
    float limit_;
};

#endif // BLOCKMANAGER_H