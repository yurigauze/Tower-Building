#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <list>
#include <vector>
#include "../Block.h"
#include "../../utils/Utils.h"
#include "../objects/Heart.h"
#include "../../Game.h" 

class Game; 

class BlockManager {
public:
    BlockManager(b2World* world, std::list<Block*>& blocks, float limit, std::list<Heart*> &hearts, Game *game);
    void update(float deltaTime);
    void destroyBlock(Block* block);
    void loseLife();

private:
    b2World* world_;
    std::list<Block*>& blocks_;
    float limit_;
    std::list<Heart*>& hearts_;
    Game *game_;
};

#endif // BLOCKMANAGER_H
