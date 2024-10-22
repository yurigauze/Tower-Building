#include "BlockManager.h"
#include "../../render/audio/AudioManager.h"
#include <algorithm>
#include <iostream>
#include "../../utils/Utils.h"

BlockManager::BlockManager(b2World *world, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game, ContactListener *contactListener, Camera *camera)
    : world_(world), blocks_(blocks), limit_(limit), hearts_(hearts), game_(game), contactListener_(contactListener), camera(camera)
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
      ++it;
    }
  }

  if (blocks_.size() > 2)
  {
    auto it = blocks_.end();
    --it;
    --it;

    Block *penultimateBlock = *it;

    if (penultimateBlock->getIsReleased())
    {
      checkBlockPositioning(penultimateBlock, contactListener_);
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

void BlockManager::checkBlockPositioning(Block *penultimateBlock, ContactListener *contactListener)
{
  std::cout << "Valor de camera em Blockmanager.cpp " << camera << std::endl;


  Block *antepenultimateBlock = nullptr;
  if (blocks_.size() > 2)
  {
    auto it = blocks_.end();
    --it;
    --it;
    --it;
    antepenultimateBlock = *it;
  }

  float referenceBlockX = BB_XPOSITION;
  bool isBaseBlock = true;

  if (antepenultimateBlock)
  {
    referenceBlockX = antepenultimateBlock->getBody()->GetPosition().x;
    isBaseBlock = false;
  }

  if (penultimateBlock->getBody()->GetLinearVelocity().Length() < 0.2f)
  {
    float penultimateBlockX = penultimateBlock->getBody()->GetPosition().x;
    float positionDifference = std::abs(penultimateBlockX - referenceBlockX);

    if (isBaseBlock)
    {
      std::cout << "Comparando com o bloco base nas coordenadas: " << BB_XPOSITION << std::endl;
    }
    else
    {
      std::cout << "Comparando com o antepenúltimo bloco nas coordenadas: " << referenceBlockX << std::endl;
    }

    std::cout << "Diferença de posição: " << positionDifference << std::endl;

    // Se a diferença estiver dentro do limite aceitável
    if (positionDifference < 2)
    {
      if (!penultimateBlock->isPositioned)
      {
        score += 10;
        std::cout << "Bônus de precisão! Pontos: 10" << std::endl;
        std::cout << "Valor de camera " << camera << std::endl;
        penultimateBlock->markAsPositioned(camera);
      }
    }
    else if (!penultimateBlock->isPositioned)
    {
      score += 5;
      std::cout << "Bloco posicionado. Pontos: 5" << std::endl;
      std::cout << "Valor de camera"  << camera << std::endl;
      penultimateBlock->markAsPositioned(camera);
    }
  }
}

void BlockManager::loseLife()
{
  // Sua lógica para perder vida (se necessário)
}