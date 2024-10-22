#include "Controller.h"
#include <iostream>
#include "../render/audio/AudioManager.h"

Controller::Controller(EventHandler *eventHandler, b2World *world, Block *&block, std::list<Block *> &gameBlocks, bool &isRunning, PortRender *renderer, BlockTest *blockTest, Camera *camera)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning), renderer_(renderer), blockTest(blockTest), camera(camera) {}

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
                    AudioManager::getInstance().playSoundEffect("block_drop");
                }
                b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
                block_ = new Block(world_, renderer_, anchorPosition, camera);
                gameBlocks_.push_back(block_);
            }

            const Uint8 *keyState = SDL_GetKeyboardState(NULL);

            if (keyState[SDL_SCANCODE_KP_0])
            {
                camera->reset(); // Chama o método reset da câmera
            }
        }
    }
}
