#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include "../Block.h"
#include "../../utils/Utils.h"
#include "../objects/Heart.h"
#include "../../Game.h"
#include "ContactListener.h"

class Game;

class BlockManager
{
public:
    BlockManager(b2World *world, Block *block, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game, ContactListener *contactListener);
    
    void update(float deltaTime);
    void destroyBlock(Block *block);
    void loseLife();

    void checkBlockPositioning(ContactListener *contactListener);
    bool isBlockPositioned(Block *block) const;
    void checkPositioning(ContactListener *contactListener);
    
    void calculateScore(Block *block);
    int getScore() const { return score; }
    int getLast() const { return last; }
    int getBlock() const { return block; }

private:
    b2World *world_;
    Block *block_;
    Block *lastPositionedBlock_;
    std::list<Block *> blocks_; 
    float limit_;
    std::list<Heart *> &hearts_;
    Game *game_;
    ContactListener *contactListener_;
    
    int score = 0;
    int last = 0;
    int block = 0;

};

#endif // BLOCKMANAGER_H
