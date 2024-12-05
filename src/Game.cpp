#include "Game.h"
#include "models/rules/BlockManager.h"
#include "controller/Controller.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include "render/audio/AudioManager.h"
#include <fstream>
#include <list>
#include <stdexcept>
#include <algorithm>

Game::Game(const char *title, int xpos, int ypos, int width, int height,
           bool fullscreen, PortRender *renderer, EventHandler *eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true), isGameOver_(false),
      lives(3)
{

  camera = new Camera(WIDTH, HEIGHT, 300);
  background = new Background(renderer, "background", "assets/background.png", camera);
  pauseBackground = new PauseBackground(renderer, "background", "assets/PauseBackground.png", camera);

  b2Vec2 gravity(0.0f, 9.81f);
  world_ = new b2World(gravity);
  debugDraw = new DebugDraw(renderer);
  world_->SetDebugDraw(debugDraw);

  contactListener_ = new ContactListener();
  world_->SetContactListener(contactListener_);

  uint32 flags = 0;
  flags |= b2Draw::e_shapeBit;
  debugDraw->SetFlags(flags);

  b2Vec2 anchorPosition(AnchorPositionX, 50);
  block_ = new Block(world_, renderer, anchorPosition, 0, camera, false, 150);
  blocks.push_back(block_);
  baseBlock = new BaseBlock(world_, renderer);

  forceApplier_ = new ForceApplier(5.0f, 1.0f, 0.0f);

  for (int i = 0; i < lives; ++i)
  {
    heart = new Heart(renderer, "heart", "assets/heart-explode.png", 10);
    hearts.push_back(heart);
  }

  blockManager_ = new BlockManager(world_, blocks, 1000.0f, hearts, this, contactListener_, camera);


  if (!renderer->loadFont("src/font/ARIAL.TTF", 24))
  {
    throw std::runtime_error("Failed to initialize font in SDLRenderer");
  }

  pauseMenu_ = new ClickableSprite("pauseBT", "assets/Pause.png", renderer);
  endBackground_ = new EndBackground(renderer, "endBackground", "assets/PauseBackground.png", camera, blockManager_);
  controller_ = new Controller(eventHandler, world_, block_, blocks, isRunning, renderer, blockTest_, camera, this, pauseBackground, endBackground_);

}

void Game::handleEvents() { controller_->handleEvents(); }

void Game::update()
{
  static float time = 0.0f;
  float deltaTime = 0.060f / 60.0f;
  time += deltaTime;

  forceApplier_->applyForce(*block_, time);

  world_->Step(deltaTime, 8, 3);

  blockManager_->update(deltaTime);

  // block_->update();

  for (auto it = hearts.begin(); it != hearts.end();)
  {
    (*it)->update(deltaTime);
    if ((*it)->isAnimationComplete())
    {
      it = hearts.erase(it);
    }
    else
    {
      ++it;
    }
  }
}

void Game::render()
{
  renderer->clear();
  background->render(HEIGHT, WIDTH);

  // world_->DebugDraw();
  // baseBlock->render(renderer, *camera);

  std::string scoreText = "Pontuacao: " + std::to_string(blockManager_->getScore());
  renderer->drawText(scoreText.c_str(), 20, 120, 255, 255, 255, 255);

  for (const auto &block : blocks)
  {
    block->render(renderer, *camera);
  }

  int x = 20;
  for (const auto &heart : hearts)
  {
    heart->render(x, 20);
    x += 50;
  }
  pauseMenu_->renderFullImage(renderer->getRenderer(), 540, 10, 50, 50);
  renderer->present();
}

void Game::clean()
{
  for (auto block : blocks)
  {
    world_->DestroyBody(block->getBody());
    delete block;
  }
  blocks.clear();

  for (auto heart : hearts)
  {
    delete heart;
  }
  hearts.clear();

  delete baseBlock;
  delete world_;
  delete debugDraw;
  delete forceApplier_;
  delete blockManager_;
  delete camera;
  delete background;
}

void Game::loseLife()
{
  if (lives > 0 && !hearts.empty())
  {
    hearts.pop_back();
    delete heart;
    --lives;

    std::cout << "Vidas restantes: " << lives << std::endl;

    if (lives == 0)
    {
      std::cerr << "Você perdeu todas as vidas!" << std::endl;
      endgame();
    }
  }
  else
  {
    std::cerr << "Erro: Não há mais corações ou vidas restantes!" << std::endl;
  }
}

void Game::endgame()
{
  isGameOver_ = true;
  // isRunning = false;
}

void Game::togglePause()
{
  paused = !paused;
}

bool Game::isPaused() const
{
  return paused;
}

void Game::renderPauseScreen()
{
  pauseBackground->render(HEIGHT, WIDTH);
  renderer->setDrawColor(0, 0, 0, 200);

  renderer->present();
}

void Game::renderEndgameScreen()
{
  endBackground_->render(HEIGHT, WIDTH);
  renderer->setDrawColor(0, 0, 0, 200);

  renderer->present();
}

void Game::resetGame()
{
  lives = 3;
  isGameOver_ = false;
  paused = false;
  background->reset();
  camera->reset();

  for (auto block : blocks)
  {
    world_->DestroyBody(block->getBody());
    delete block;
  }
  blocks.clear();

  block_ = new Block(world_, renderer, b2Vec2(AnchorPositionX, 50), 0, camera, false, 150);
  blocks.push_back(block_);
  blockManager_->resetScore();

  for (auto heart : hearts)
  {
    delete heart;
  }
  hearts.clear();
  for (int i = 0; i < lives; ++i)
  {
    heart = new Heart(renderer, "heart", "assets/heart-explode.png", 10);
    hearts.push_back(heart);
  }



  AudioManager::getInstance().playMusic("bgm");
}

void Game::startNewGame()
{
  resetGame();
}
