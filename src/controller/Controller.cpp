#include "Controller.h"
#include <iostream>
#include "../render/audio/AudioManager.h"

Controller::Controller(EventHandler *eventHandler, b2World *world, Block *&block, std::list<Block *> &gameBlocks, bool &isRunning, PortRender *renderer, BlockTest *blockTest, Camera *camera, Game *game, PauseBackground *pauseBackground, EndBackground *endBackground)
    : eventHandler_(eventHandler), world_(world), block_(block),
      gameBlocks_(gameBlocks), isRunning_(isRunning), renderer_(renderer), blockTest(blockTest), camera(camera), game(game), pauseBackground(pauseBackground), endBackground(endBackground), userInput("") {}

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
            // Lógica para liberar o bloco
            if (eventHandler_->getKeyCode() == SDLK_SPACE && !game->isPaused())
            {
                if (!block_->getIsReleased())
                {
                    block_->release();
                    AudioManager::getInstance().playSoundEffect("block_drop");
                }

                b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
                block_ = new Block(world_, renderer_, anchorPosition, 150, camera, true);
                gameBlocks_.push_back(block_);
            }

            const Uint8 *keyState = SDL_GetKeyboardState(NULL);

            // Resetar a câmera com a tecla 0
            if (keyState[SDL_SCANCODE_KP_0] && !game->isPaused())
            {
                camera->reset();
            }

            // Pausar o jogo com a tecla P
            if (eventHandler_->getKeyCode() == SDLK_p)
            {
                game->togglePause();
            }

            // Captura a tecla 'Enter' para salvar o score
            if (eventHandler_->getKeyCode() == SDLK_RETURN && game->isGameOver())
            {
                endBackground->saveScore(userInput); // Passa o nome do jogador para a função saveScore
            }

            // Tecla BACKSPACE para apagar o último caractere
            if (eventHandler_->getKeyCode() == SDLK_BACKSPACE && game->isGameOver() && !userInput.empty())
            {
                userInput.pop_back();
            }

            // Captura qualquer tecla alfanumérica para digitar o nome do jogador
            if (eventHandler_->getKeyCode() >= SDLK_a && eventHandler_->getKeyCode() <= SDLK_z)
            {
                if (game->isGameOver())
                {
                    userInput += eventHandler_->getKeyCode();
                }
            }
        }

        // Captura de clique do mouse
        if (eventHandler_->getEventType() == SDL_MOUSEBUTTONDOWN)
        {
            int mouseX = eventHandler_->getMouseX();
            int mouseY = eventHandler_->getMouseY();

            // Lógica para o botão "Novo Jogo" no menu de pausa
            if (pauseBackground->getButtonNG()->isClicked(mouseX, mouseY) && game->isPaused())
            {
                std::cout << "Botão New Game clicado!" << std::endl;
                // Lógica para iniciar um novo jogo
                // game->startNewGame();
            }

            // Lógica para o botão "Continuar" no menu de pausa
            if (pauseBackground->getButtonContinue()->isClicked(mouseX, mouseY) && game->isPaused())
            {
                std::cout << "Botão Continue clicado!" << std::endl;
                game->togglePause();
            }

            // Lógica para o botão "Novo Jogo" após o Game Over
            if (endBackground->getButtonnewGame()->isClicked(mouseX, mouseY) && game->isGameOver())
            {
                std::cout << "Botão NewGame clicado!" << std::endl;
                game->startNewGame();
            }

            // Alterna entre pausa e jogo com clique
            if (game->getPauseMenu()->isClicked(mouseX, mouseY) && !game->isPaused())
            {
                game->togglePause();
            }
        }
    }
}
