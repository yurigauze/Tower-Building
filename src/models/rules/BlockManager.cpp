#include "BlockManager.h"
#include "../../render/audio/AudioManager.h"
#include <algorithm>
#include <iostream>

BlockManager::BlockManager(b2World *world, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game)
    : world_(world), blocks_(blocks), limit_(limit), hearts_(hearts), game_(game)  {
    std::cout << "Número de corações no BlockManager: " << hearts_.size() << std::endl;
}

void BlockManager::update(float deltaTime) {
  // Atualizar os blocos
  for (auto it = blocks_.begin(); it != blocks_.end();) {
    Block *block = *it;
    b2Vec2 position = block->getBody()->GetPosition();

    if (metersToPixels(position.y) > limit_) {
      std::cout << "Bloco fora dos limites: " << block << std::endl;
      AudioManager::getInstance().playSoundEffect("destroy");

      // Destruir o bloco
      destroyBlock(block);
      it = blocks_.erase(it);

      // Perde uma vida (marcando o coração como perdido)
      if (!hearts_.empty()) {
        std::cout << "Marcando o coração como perdido." << std::endl;
        hearts_.back()->loseHeart(); // Inicia a animação do coração perdido
        // game_->loseLife();           // Atualiza o estado do jogo imediatamente
      }

    } else {
      ++it;
    }
  }
  
  // Atualizar os corações
  std::cout << "Número de corações antes da atualização: " << hearts_.size() << std::endl;
  for (auto it = hearts_.begin(); it != hearts_.end();) {
    Heart *heart = *it;
    std::cout << "Atualizando coração: " << heart << std::endl;
    heart->update(deltaTime);

    // Somente verifica a animação se o coração estiver perdido
    if (heart->isAnimationComplete() && heart->isLostHeart()) {
      std::cout << "Animação do coração concluída: " << heart << std::endl;
      it = hearts_.erase(it);  // Remove o coração após a animação ser concluída
    } else {
      ++it;
    }
  }
  std::cout << "Número de corações após a atualização: " << hearts_.size() << std::endl;
}


void BlockManager::destroyBlock(Block *block) {
  if (block) {
    world_->DestroyBody(block->getBody());
    delete block;
  }
}

void BlockManager::loseLife() {
  std::cout << "Uma vida foi sinalizada como perdida!" << std::endl;
}
