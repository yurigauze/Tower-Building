#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <list>
#include <vector>
#include "../Block.h"
#include "../../utils/Utils.h"
#include "../objects/Heart.h"

class BlockManager {
public:
    BlockManager(b2World* world, std::list<Block*>& blocks, float limit, std::vector<Heart*> &hearts);
    void update(float deltaTime);
    void loseLife();
    void destroyBlock(Block* block);

private:
    b2World* world_;
    std::list<Block*>& blocks_;
    float limit_;
    std::vector<Heart*>& hearts_;

};

#endif // BLOCKMANAGER_H