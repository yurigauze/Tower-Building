#include "BlockManager.h"
#include <algorithm>
#include <iostream>

BlockManager::BlockManager(b2World *world, std::list<Block *> &blocks,
                           float limit)
    : world_(world), blocks_(blocks), limit_(limit) {}

void BlockManager::update(float deltaTime) {
  for (auto it = blocks_.begin(); it != blocks_.end();) {
    Block *block = *it;
    b2Vec2 position = block->getBody()->GetPosition();

    // Verificar se o bloco está fora dos limites
    if (metersToPixels(position.y) > limit_) {
      std::cout << "Bloco fora dos limites: " << block << std::endl;
      destroyBlock(block);
      it = blocks_.erase(it);
    } else {
      ++it;
    }
  }
}
void BlockManager::destroyBlock(Block *block) {
  if (block) {
    world_->DestroyBody(block->getBody());
    delete block; // Libera a memória associada ao bloco
  }
}
