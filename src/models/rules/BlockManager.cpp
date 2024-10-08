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

void BlockManager::checkBlockPositioning(Block *newBlock, ContactListener *contactListener)
{

  if (blocks_.size() > 1 && newBlock && newBlock->getIsReleased() && newBlock->isInContactWithAnotherBlock(contactListener))
  {
    Block* lastPositionedBlock = nullptr;
    for (auto it = blocks_.rbegin(); it != blocks_.rend(); ++it)
    {
      if ((*it)->isPositioned) 
      {
        lastPositionedBlock = *it;
        break;
      }
    }

    if (!lastPositionedBlock) 
    {
      std::cout << "Nenhum bloco posicionado anterior encontrado." << std::endl;
      return;
    }

    if (newBlock->isPositioned)
    {
      std::cout << "Novo bloco já posicionado. Nenhuma ação necessária." << std::endl;
      return;
    }

    if (newBlock->getBody()->GetLinearVelocity().Length() < 0.1f)
    {
      float newBlockRenderX = metersToPixels(newBlock->getBody()->GetPosition().x);
      float lastBlockRenderX = metersToPixels(lastPositionedBlock->getBody()->GetPosition().x);

      int positionDifference = std::abs(newBlockRenderX - lastBlockRenderX);

      std::cout << "newBlock (render): " << newBlockRenderX << std::endl;
      std::cout << "lastBlock (render): " << lastBlockRenderX << std::endl;
      std::cout << "positionDifference (pixels): " << positionDifference << std::endl;

      int precisionThreshold = 2;
      std::cout << "precisionThreshold: " << precisionThreshold << std::endl;

      if (positionDifference <= precisionThreshold)
      {
        score += 10;
        std::cout << "Bônus de precisão! Pontos: 10" << std::endl;
        newBlock->markAsPositioned();
      }
      else
      {
        score += 5;
        std::cout << "Bloco posicionado. Pontos: 5" << std::endl;
        newBlock->markAsPositioned();
      }
    }
  }
}



void BlockManager::loseLife()
{
  // Sua lógica para perder vida (se necessário)
}
