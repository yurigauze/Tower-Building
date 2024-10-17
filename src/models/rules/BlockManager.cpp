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

bool BlockManager::isBlockPositioned(Block *block) const {
    return block && block->isPositioned; 
}

void BlockManager::checkBlockPositioning(Block *lastBlock, ContactListener *contactListener) {
    if (blocks_.size() > 1 && lastBlock && lastBlock->getIsReleased() && lastBlock->isInContactWithAnotherBlock(contactListener)) {
        Block *previousBlock = *(--blocks_.end());

        if (lastBlock->getBody()->GetLinearVelocity().Length() < 0.1f) {
            float lastBlockX = lastBlock->getBody()->GetPosition().x;
            float previousBlockX = previousBlock->getBody()->GetPosition().x;
            float positionDifference = std::abs(lastBlockX - previousBlockX);

            // Se a posição do último bloco estiver próxima do bloco anterior
            if (!lastBlock->isPositioned) {
                if (positionDifference < 2) {
                    score += 10; // Bônus de precisão
                    lastBlock->markAsPositioned();
                } else {
                    score += 5;
                    lastBlock->markAsPositioned();
                }
            }
        }
    }
}

// Adicione este método para verificar se o bloco atual é o bloco no gancho
bool BlockManager::isBlockOnHookActive(Block *block) const {
    return block && !block->getIsReleased();
}

void BlockManager::loseLife()
{
    // Sua lógica para perder vida (se necessário)
}
