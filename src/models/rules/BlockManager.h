#ifndef BLOCKMANAGER_H
#define BLOCKMANAGER_H

#include <list>
#include <vector>
#include "../Block.h"
#include "../../utils/Utils.h"
#include "../objects/Heart.h"
#include "../../Game.h"
#include "../../logger/ConsoleLogger.h"
#include "../../logger/ILogger.h"
#include "../../render/audio/IAudioManager.h"

class Game;

class BlockManager
{
public:
    BlockManager(b2World *world, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game, ContactListener *contactListener, ILogger *logger, IAudioManager *audioManager);
    
    void update(float deltaTime);
    void calculateScore(Block *block);
    void destroyBlock(Block *block);
    int getScore() const { return score; }
    void loseLife();

private:
    b2World *world_;
    std::list<Block *> &blocks_;
    float limit_;
    std::list<Heart *> &hearts_;
    Game *game_;
    int score = 0;
    ContactListener *contactListener_;
    ILogger *logger_;
    IAudioManager *audioManager_; 
    void checkBlockPositioning(Block *lastBlock, ContactListener *contactListener);
};

#endif
