#include "BlockManager.h"
#include "../../render/audio/AudioManager.h"
#include <algorithm>
#include <iostream>

BlockManager::BlockManager(b2World *world, std::list<Block *> &blocks,
                           float limit, std::vector<Heart *> &hearts)
    : world_(world), blocks_(blocks), limit_(limit), hearts_(hearts) {}

void BlockManager::update(float deltaTime) {
  for (auto it = blocks_.begin(); it != blocks_.end();) {
    Block *block = *it;
    b2Vec2 position = block->getBody()->GetPosition();

    if (metersToPixels(position.y) > limit_) {
      std::cout << "Bloco fora dos limites: " << block << std::endl;
      AudioManager::getInstance().playSoundEffect("destroy");
      destroyBlock(block);
      it = blocks_.erase(it);
      loseLife();
    } else {
      ++it;
    }
  }
  for (auto &heart : hearts_) {
    heart->update(deltaTime);
  }
}

void BlockManager::destroyBlock(Block *block) {
  if (block) {
    world_->DestroyBody(block->getBody());
    delete block;
  }
}

void BlockManager::loseLife() {
  if (!hearts_.empty()) {
    Heart *heart = hearts_.back();
    hearts_.pop_back();
    heart->loseHeart();
    std::cout << "Uma vida foi perdida!" << std::endl;
    std::cout << "Coração perdido: " << heart << std::endl;
  } else {
    std::cout << "Todas as vidas foram perdidas!" << std::endl;
  }
}
