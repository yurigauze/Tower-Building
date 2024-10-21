#include "BlockManager.h"
#include "../../render/audio/AudioManager.h"
#include <iostream>
#include "../../utils/Utils.h"

BlockManager::BlockManager(b2World *world, Block *block, std::list<Block *> &blocks, float limit, std::list<Heart *> &hearts, Game *game, ContactListener *contactListener)
    : world_(world), block_(block), blocks_(blocks), limit_(limit), hearts_(hearts), game_(game), contactListener_(contactListener), lastPositionedBlock_(nullptr)
{
}

void BlockManager::update(float deltaTime)
{
    if (block_)
    {
        b2Vec2 position = block_->getBody()->GetPosition();
        std::cout << "Current block position (y): " << metersToPixels(position.y) << std::endl;

        checkPositioning(contactListener_);

        if (block_->isPositioned())
        {
            // Agora sim, o bloco pode ser adicionado à lista
            game_->addBlockToList(block_);
            std::cerr << "Bloco posicionado e adicionado à lista!" << std::endl;

            // Em seguida, crie um novo bloco
            block_ = game_->createNewBlock();
        }

        if (metersToPixels(position.y) > limit_)
        {
            AudioManager::getInstance().playSoundEffect("destroy");
            std::cerr << "Destruindo bloco: " << block_ << std::endl;
            game_->destroyBlock(block_);
            block_ = nullptr;

            if (!hearts_.empty())
            {
                hearts_.back()->loseHeart();
            }
            block_ = game_->createNewBlock();
            std::cerr << "Novo bloco criado: " << block_ << std::endl;
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
        // Primeiro remova o bloco da lista
        blocks_.remove(block); // Remove o bloco da lista antes de destruí-lo
        world_->DestroyBody(block->getBody());
        std::cout << "Destruindo bloco em: " << block->getBody()->GetPosition().y << std::endl;
        delete block;
        block = nullptr;
    }
}

void BlockManager::checkPositioning(ContactListener *contactListener)
{
    if (block_)
    {
        b2Vec2 fallingBlockPosition = block_->getBody()->GetPosition();
        std::cout << "Verificando posicionamento para o bloco em: " << fallingBlockPosition.x << ", " << fallingBlockPosition.y << std::endl;

        if (!block_->isInContactWithAnotherBlock(contactListener))
        {
            std::cout << "O bloco não está em contato com outro bloco. Cancelando o posicionamento." << std::endl;
            return;
        }

        if (lastPositionedBlock_ == nullptr)
        {
            bool isAboveBase = fallingBlockPosition.y >= 24.980;
            std::cout << "isAboveBase: " << isAboveBase << std::endl;

            if (isAboveBase)
            {
                block_->markAsPositioned();
                lastPositionedBlock_ = block_;
                std::cout << "O bloco foi posicionado sobre o bloco base." << std::endl;
            }
        }
        else
        {
            b2Vec2 lastBlockPosition = lastPositionedBlock_->getBody()->GetPosition();
            bool isAboveLastBlock = fallingBlockPosition.y + (BLOCK_HEIGHT / 2.0f) >= lastBlockPosition.y;

            std::cout << "Posição do último bloco: " << lastBlockPosition.x << ", " << lastBlockPosition.y << std::endl;
            std::cout << "Posição do bloco " << fallingBlockPosition.x << ", " << fallingBlockPosition.y << std::endl;
            std::cout << "isAboveLastBlock: " << isAboveLastBlock << std::endl;

            if (isAboveLastBlock)
            {
                block_->markAsPositioned();
                lastPositionedBlock_ = block_;
                std::cout << "O bloco foi posicionado sobre o último bloco." << std::endl;
            }
        }
    }
}

bool BlockManager::isBlockPositioned(Block *block) const
{
    return block && block->isPositioned();
}

void BlockManager::checkBlockPositioning(ContactListener *contactListener)
{
    if (block_ && block_->getIsReleased() && block_->isInContactWithAnotherBlock(contactListener))
    {
        if (block_->getBody()->GetLinearVelocity().Length() < 0.1f)
        {
            block_->markAsPositioned();
        }
    }
}

void BlockManager::loseLife()
{
    // Sua lógica para perder vida (se necessário)
}
