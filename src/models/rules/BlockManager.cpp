#include "BlockManager.h"
#include "../../render/audio/AudioManager.h"
#include <algorithm>
#include <iostream>
#include "../../utils/Utils.h"

BlockManager::BlockManager(b2World *world, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game, ContactListener *contactListener)
    : world_(world), blocks_(blocks), limit_(limit), hearts_(hearts), game_(game), contactListener_(contactListener)
{
}

void BlockManager::update(float deltaTime)
{

  for (auto it = blocks_.begin(); it != blocks_.end();)
  {
    Block *block = *it;
    b2Vec2 position = block->getBody()->GetPosition();

    if (metersToPixels(position.y) > limit_)
    {
      AudioManager::getInstance().playSoundEffect("destroy");
      destroyBlock(block);
      it = blocks_.erase(it);

      if (!hearts_.empty())
      {
        hearts_.back()->loseHeart();
      }
    }
    else
    {
      checkBlockPositioning(block, contactListener_);
      ++it;
    }
  }

  for (auto it = hearts_.begin(); it != hearts_.end();)
  {
    Heart *heart = *it;
    heart->update(deltaTime);

    if (heart->isAnimationComplete() && heart->isLostHeart())
    {
      it = hearts_.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void BlockManager::destroyBlock(Block *block)
{
  if (block)
  {
    world_->DestroyBody(block->getBody());
    delete block;
  }
}

void BlockManager::checkBlockPositioning(Block *lastBlock, ContactListener *contactListener)
{
  if (blocks_.size() > 1 && lastBlock && lastBlock->getIsReleased() && lastBlock->isInContactWithAnotherBlock(contactListener))
  {
    Block *previousBlock = *(--blocks_.end());

    if (lastBlock->getBody()->GetLinearVelocity().Length() < 0.1f)
    {
      float lastBlockX = lastBlock->getBody()->GetPosition().x;
      float previousBlockX = previousBlock->getBody()->GetPosition().x;

      float positionDifference = std::abs(lastBlockX - previousBlockX);
      std::cout << "ultimo bloco" << lastBlockX << std::endl;
      std::cout << "bloco a ser solto " << previousBlockX << std::endl;

      std::cout << "Diferença de posição: " << positionDifference << std::endl;

      if (positionDifference < 2)
      {
        if (!lastBlock->isPositioned)
        {
          score += 10;
          std::cout << "Bônus de precisão! Pontos: 10" << std::endl;
          lastBlock->markAsPositioned();
        }
      }
      else if (!lastBlock->isPositioned)
      {
        score += 5;
        std::cout << "Bloco posicionado. Pontos: 5" << std::endl;
        lastBlock->markAsPositioned();
      }
    }
  }
}

void BlockManager::loseLife()
{
  // Sua lógica para perder vida (se necessário)
}
