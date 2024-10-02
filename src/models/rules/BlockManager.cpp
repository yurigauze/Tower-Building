#include "BlockManager.h"
#include "../../render/audio/AudioManager.h"
#include <algorithm>
#include <iostream>

BlockManager::BlockManager(b2World *world, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game)
    : world_(world), blocks_(blocks), limit_(limit), hearts_(hearts), game_(game)  {
}

void BlockManager::update(float deltaTime) {
  for (auto it = blocks_.begin(); it != blocks_.end();) {
    Block *block = *it;
    b2Vec2 position = block->getBody()->GetPosition();

    if (metersToPixels(position.y) > limit_) {
      AudioManager::getInstance().playSoundEffect("destroy");

      destroyBlock(block);
      it = blocks_.erase(it);

      if (!hearts_.empty()) {
        hearts_.back()->loseHeart(); 
      }

    } else {
      ++it;
    }
  }
  

  for (auto it = hearts_.begin(); it != hearts_.end();) {
    Heart *heart = *it;
    heart->update(deltaTime);

    if (heart->isAnimationComplete() && heart->isLostHeart()) {
      it = hearts_.erase(it);
    } else {
      ++it;
    }
  }
}


void BlockManager::destroyBlock(Block *block) {
  if (block) {
    world_->DestroyBody(block->getBody());
    delete block;
  }
}

void BlockManager::loseLife() {
}
