#include "Controller.h"
#include <iostream>
#include "../render/audio/AudioManager.h"

Controller::Controller(EventHandler *eventHandler, b2World *world, Block *&block, std::list<Block *> &gameBlocks, bool &isRunning, PortRender *renderer, BlockTest *blockTest, Camera *camera, Game *game, PauseBackground *pauseBackground)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning), renderer_(renderer), blockTest(blockTest), camera(camera), game(game), pauseBackground(pauseBackground) {}

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

            if (eventHandler_->getKeyCode() == SDLK_SPACE && !game->isPaused())
            {
                if (!block_->getIsReleased())
                {
                    block_->release();
                    AudioManager::getInstance().playSoundEffect("block_drop");
                }

                b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
                block_ = new Block(world_, renderer_, anchorPosition, 150, camera, true );
                gameBlocks_.push_back(block_);
            }

            const Uint8 *keyState = SDL_GetKeyboardState(NULL);

            if (keyState[SDL_SCANCODE_KP_0] && !game->isPaused())
            {
                camera->reset();
            }

            if (eventHandler_->getKeyCode() == SDLK_p)
            {
                game->togglePause();
            }
        }
        if (eventHandler_->getEventType() == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX = eventHandler_->getMouseX();
            int mouseY = eventHandler_->getMouseY();


            if (pauseBackground->getButtonNG()->isClicked(mouseX, mouseY) && game->isPaused())
            {
                std::cout << "Botão New Game clicado!" << std::endl;
                // Lógica para iniciar um novo jogo
                // game->startNewGame();
            }

            if (pauseBackground->getButtonContinue()->isClicked(mouseX, mouseY) && game->isPaused())
            {
                std::cout << "Botão Continue clicado!" << std::endl;
                game->togglePause();
            }

            if (game->getPauseMenu()->isClicked(mouseX, mouseY) && !game->isPaused()){
                game->togglePause();
            }
        }
    }
}
