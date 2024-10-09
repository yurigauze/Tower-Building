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
      // Verifique se o bloco foi liberado antes de chamar a verificação de posicionamento
      if (block->getIsReleased())
      {
        checkBlockPositioning(block, contactListener_);
      }
      else
      {
        std::cout << "Bloco não liberado: " << block << std::endl; // Log de depuração
      }
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
  std::cout << "Verificando posicionamento do bloco: " << newBlock << std::endl; // Log de depuração

  if (blocks_.size() > 1 && newBlock && newBlock->getIsReleased())
  {
    std::cout << "Novo bloco liberado, verificando contato..." << std::endl;

    if (newBlock->isInContactWithAnotherBlock(contactListener))
    {
      Block *lastPositionedBlock = nullptr;

      // Encontra o último bloco posicionado
      for (auto it = blocks_.rbegin(); it != blocks_.rend(); ++it)
      {
        if ((*it)->isPositioned)
        {
          std::cout << "Bloco posicionado: " << (*it) << std::endl;
          lastPositionedBlock = *it;
          break;
        }
      }

      if (!lastPositionedBlock)
      {
        std::cout << "Nenhum bloco posicionado anterior encontrado." << std::endl;
        return;
      }

      // Verificação se o novo bloco já está posicionado
      if (newBlock->isPositioned)
      {
        std::cout << "Novo bloco já posicionado. Nenhuma ação necessária." << std::endl;
        return;
      }

      // Verifica se o bloco está parado e em contato
      b2Vec2 linearVelocity = newBlock->getBody()->GetLinearVelocity();
      std::cout << "Velocidade do novo bloco: " << linearVelocity.Length() << std::endl;

      if (linearVelocity.Length() < 0.1f)
      {
        std::cout << "O bloco está parado e em contato." << std::endl;
        float newBlockRenderX = metersToPixels(newBlock->getBody()->GetPosition().x);
        float lastBlockRenderX = metersToPixels(lastPositionedBlock->getBody()->GetPosition().x);

        int positionDifference = std::abs(newBlockRenderX - lastBlockRenderX);
        std::cout << "Nova diferença de posição: " << positionDifference << std::endl;

        int precisionThreshold = 2;

        if (positionDifference <= precisionThreshold)
        {
          score += 10;
          std::cout << "Bônus de precisão! Pontos: 10" << std::endl;
        }
        else
        {
          score += 5;
          std::cout << "Bloco posicionado. Pontos: 5" << std::endl;
        }

        // Marca como posicionado
        newBlock->markAsPositioned();
        std::cout << "Novo bloco marcado como posicionado." << std::endl;
      }
      else
      {
        std::cout << "Novo bloco não está parado." << std::endl;
      }
    }
    else
    {
      std::cout << "Novo bloco não está em contato com outro bloco." << std::endl;
    }
  }
  else
  {
    std::cout << "Condições não atendidas para verificação de posicionamento." << std::endl;
  }
}

void BlockManager::loseLife()
{
  // Sua lógica para perder vida (se necessário)
}
