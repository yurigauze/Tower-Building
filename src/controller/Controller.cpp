#include "Controller.h"
#include <iostream>
#include "../render/audio/AudioManager.h"

Controller::Controller(EventHandler *eventHandler, b2World *world, Block *&block, std::list<Block *> &gameBlocks, bool &isRunning, PortRender *renderer, BlockTest *blockTest, Camera *camera, BlockManager *blockManager, bool &isBlockOnHookActive)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning), renderer_(renderer), blockTest(blockTest), blockManager_(blockManager), isBlockOnHookActive(isBlockOnHookActive) {}

void Controller::handleEvents()
{
    while (eventHandler_->pollEvent())
    {
        if (eventHandler_->isQuitEvent())
        {
            isRunning_ = false;
        }
        else if (eventHandler_->isKeyDownEvent())
        {
            if (eventHandler_->getKeyCode() == SDLK_SPACE)
            {
                // Se o bloco está no gancho e ainda não foi solto
                if (!block_->getIsReleased() && isBlockOnHookActive)
                {
                    block_->release(); // Solta o bloco
                    AudioManager::getInstance().playSoundEffect("block_drop");
                    isBlockOnHookActive = false; // Agora, não há bloco no gancho
                }
                // Se o bloco já foi solto e não está mais no gancho
                else if (block_->getIsReleased() && !isBlockOnHookActive)
                {
                    // Verifique se o bloco foi posicionado corretamente
                    if (blockManager_->isBlockPositioned(block_))
                    {
                        // Cria um novo bloco no gancho
                        b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
                        Block *newBlock = new Block(world_, renderer_, anchorPosition);
                        // Adiciona a lógica para adicionar o bloco à lista em outro lugar
                        addBlockIfPositioned(newBlock);
                        isBlockOnHookActive = true; // Agora, temos um novo bloco no gancho
                    }
                }
            }

            const Uint8 *keyState = SDL_GetKeyboardState(NULL);

            if (blockTest != nullptr)
            {
                if (keyState[SDL_SCANCODE_LEFT])
                {
                    b2Vec2 velocity = blockTest->getBody()->GetLinearVelocity();
                    velocity.x = -0.5f;
                    blockTest->getBody()->SetLinearVelocity(velocity);
                    std::cerr << "Se moveu LEFT" << std::endl;
                }
                else if (keyState[SDL_SCANCODE_RIGHT])
                {
                    b2Vec2 velocity = blockTest->getBody()->GetLinearVelocity();
                    velocity.x = 0.5f;
                    blockTest->getBody()->SetLinearVelocity(velocity);
                    std::cerr << "Se moveu RIGHT" << std::endl;
                }

                else if (keyState[SDL_SCANCODE_UP])
                {
                    b2Vec2 velocity = blockTest->getBody()->GetLinearVelocity();
                    velocity.y = -0.5f;
                    blockTest->getBody()->SetLinearVelocity(velocity);
                    std::cerr << "Se moveu UP" << std::endl;
                }
                else if (keyState[SDL_SCANCODE_0])
                {
                    b2Vec2 velocity = blockTest->getBody()->GetLinearVelocity();
                    velocity.y = 0.0;
                    velocity.x = 0.0;
                    blockTest->getBody()->SetLinearVelocity(velocity);
                    std::cerr << "parou" << std::endl;
                }
                else if (keyState[SDL_SCANCODE_DOWN])
                {
                    b2Vec2 velocity = blockTest->getBody()->GetLinearVelocity();
                    velocity.y = 0.5f;
                    blockTest->getBody()->SetLinearVelocity(velocity);
                    std::cerr << "Se moveu DOWN" << std::endl;
                }
            }
            else
            {
                std::cerr << "blockTest é nulo!" << std::endl;
            }
        }
    }
}

void Controller::addBlockIfPositioned(Block *newBlock)
{
    if (blockManager_->isBlockPositioned(newBlock))
    {
        gameBlocks_.push_back(newBlock); // Adiciona o bloco à lista somente se posicionado
    }
    else
    {
        delete newBlock; // Libera a memória se não for posicionado
    }
}