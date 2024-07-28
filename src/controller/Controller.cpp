// Controller.cpp
#include "Controller.h"

Controller::Controller(EventHandler *eventHandler, b2World *world,
                       Block *&block, std::list<Block *> &gameBlocks,
                       bool &isRunning)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning) {}

void Controller::handleEvents() {
  while (eventHandler_->pollEvent()) {
    if (eventHandler_->isQuitEvent()) {
      isRunning_ = false;
    } else if (eventHandler_->isKeyDownEvent()) {
      if (eventHandler_->getKeyCode() == SDLK_SPACE) {
        if (!block_->getIsReleased()) {
          block_->release();
        }

        b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
        block_ = new Block(world_, anchorPosition);
        gameBlocks_.push_back(block_);
      }
    }
  }
}
