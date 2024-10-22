#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <list>
#include <vector>
#include "../Block.h"
#include "../../utils/Utils.h"
#include "../objects/Heart.h"
#include "../../Game.h"
#include "ContactListener.h"
#include "../../render/Camera.h"

class Game;

class BlockManager
{
public:
    void calculateScore(Block *block);
    int getScore() const { return score; }
    int getlast() const { return last; }
    int getblock() const { return block; }

    BlockManager(b2World *world, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game, ContactListener *contactListener, Camera *camera);
    void update(float deltaTime);
    void destroyBlock(Block *block);
    void loseLife();

private:
    b2World *world_;
    std::list<Block *> &blocks_;
    float limit_;
    std::list<Heart *> &hearts_;
    Game *game_;
    int score = 0;
    int last = 0;
    int block = 0;
    void checkBlockPositioning(Block *lastBlock, ContactListener *contactListener);
    ContactListener *contactListener_;
    Camera *camera;

};

#endif // BLOCKMANAGER_H
