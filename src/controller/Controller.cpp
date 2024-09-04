#include "Controller.h"
#include <iostream>
#include "../render/audio/AudioManager.h"

Controller::Controller(EventHandler *eventHandler, b2World *world,
                       Block *&block, std::list<Block *> &gameBlocks,
                       bool &isRunning, PortRender *renderer)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning), renderer_(renderer) {}

void Controller::handleEvents() {
    while (eventHandler_->pollEvent()) {
        if (eventHandler_->isQuitEvent()) {
            isRunning_ = false;
        } else if (eventHandler_->isKeyDownEvent()) {
            if (eventHandler_->getKeyCode() == SDLK_SPACE) {
                if (!block_->getIsReleased()) {
                    block_->release();
                    AudioManager::getInstance().playSoundEffect("block_drop");
                }

                // Instanciar o novo bloco e adicioná-lo à lista
                b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
                block_ = new Block(world_, renderer_, anchorPosition);
                gameBlocks_.push_back(block_);

                // Depuração
                std::cout << "Novo bloco adicionado ao jogo." << std::endl;
            }
        }
    }
}

