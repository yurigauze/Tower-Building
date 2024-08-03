#include "BlockManager.h"
#include <algorithm>
#include <iostream>

BlockManager::BlockManager(b2World* world, std::list<Block*>& blocks, float limit)
    : world_(world), blocks_(blocks), limit_(limit) {}

void BlockManager::update(float deltaTime) {
    for (auto it = blocks_.begin(); it != blocks_.end();) {
        Block* block = *it;
        b2Vec2 position = block->getBody()->GetPosition();
        if (metersToPixels(position.y) > limit_) {
            destroyBlock(block);
            std::cout << "Bloco Destruído" << std::endl;
            it = blocks_.erase(it);
        } else {
            ++it;
        }
    }
}

void BlockManager::destroyBlock(Block* block) {
    world_->DestroyBody(block->getBody());
    delete block;
}