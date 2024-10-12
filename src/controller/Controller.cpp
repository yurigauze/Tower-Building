#include "Controller.h"
#include <iostream>

Controller::Controller(EventHandler *eventHandler, b2World *world,
                       Block *&block, std::list<Block *> &gameBlocks,
                       bool &isRunning, PortRender *renderer, 
                       BlockTest *blockTest, ILogger* logger, IAudioManager* audioManager)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning), 
      renderer_(renderer), blockTest_(blockTest), 
      logger_(logger), audioManager_(audioManager) {} 

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
                if (!block_->getIsReleased())
                {
                    block_->release();
                    audioManager_->playSoundEffect("block_drop");
                }
                b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
                block_ = new Block(world_, renderer_, anchorPosition, logger_);
                gameBlocks_.push_back(block_);
            }

            const Uint8 *keyState = SDL_GetKeyboardState(NULL);

            if (blockTest_ != nullptr)
            {
                if (keyState[SDL_SCANCODE_LEFT])
                {
                    b2Vec2 velocity = blockTest_->getBody()->GetLinearVelocity();
                    velocity.x = -0.5f;
                    blockTest_->getBody()->SetLinearVelocity(velocity);
                    logger_->Log("Se moveu LEFT");
                }
                else if (keyState[SDL_SCANCODE_RIGHT])
                {
                    b2Vec2 velocity = blockTest_->getBody()->GetLinearVelocity();
                    velocity.x = 0.5f;
                    blockTest_->getBody()->SetLinearVelocity(velocity);
                    logger_->Log("Se moveu RIGHT");
                }
                else if (keyState[SDL_SCANCODE_UP])
                {
                    b2Vec2 velocity = blockTest_->getBody()->GetLinearVelocity();
                    velocity.y = -0.5f;
                    blockTest_->getBody()->SetLinearVelocity(velocity);
                    logger_->Log("Se moveu UP"); 
                }
                else if (keyState[SDL_SCANCODE_0])
                {
                    b2Vec2 velocity = blockTest_->getBody()->GetLinearVelocity();
                    velocity.y = 0.0;
                    velocity.x = 0.0;
                    blockTest_->getBody()->SetLinearVelocity(velocity);
                    logger_->Log("Parou"); 
                }
                else if (keyState[SDL_SCANCODE_DOWN])
                {
                    b2Vec2 velocity = blockTest_->getBody()->GetLinearVelocity();
                    velocity.y = 0.5f;
                    blockTest_->getBody()->SetLinearVelocity(velocity);
                    logger_->Log("Se moveu DOWN"); 
                }
            }
            else
            {
                logger_->Log("blockTest é nulo!"); 
            }
        }
    }
}
