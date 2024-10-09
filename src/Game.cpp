#include "Game.h"
#include "models/rules/BlockManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <list>
#include <stdexcept>

Game::Game(const char *title, int xpos, int ypos, int width, int height,
           bool fullscreen, PortRender *renderer, EventHandler *eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true),
      lives(3)
{

  b2Vec2 gravity(0.0f, 9.81f);
  world_ = new b2World(gravity);
  debugDraw = new DebugDraw(renderer);
  world_->SetDebugDraw(debugDraw);

  contactListener_ = new ContactListener();
  world_->SetContactListener(contactListener_);

  uint32 flags = 0;
  flags |= b2Draw::e_shapeBit;
  debugDraw->SetFlags(flags);
  b2Vec2 initialPosition(500, 500);
  blockTest_ = new BlockTest(world_, renderer, initialPosition);

  controller_ =
      new Controller(eventHandler, world_, block_, blocks, isRunning, renderer, blockTest_);

  b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
  block_ = new Block(world_, renderer, anchorPosition);
  blocks.push_back(block_);
  baseBlock = new BaseBlock(world_, renderer);

  forceApplier_ = new ForceApplier(5.0f, 1.0f, 0.0f);

  for (int i = 0; i < lives; ++i)
  {
    Heart *heart = new Heart(renderer, "heart", "assets/heart-explode.png", 10);
    hearts.push_back(heart);
  }

  blockManager_ = new BlockManager(world_, blocks, 1000.0f, hearts, this, contactListener_);

  if (!renderer->loadFont("src/font/ARIAL.TTF", 24))
  {
    throw std::runtime_error("Failed to initialize font in SDLRenderer");
  }
}

void Game::handleEvents() { controller_->handleEvents(); }

void Game::update()
{
  static float time = 0.0f;
  float deltaTime = 0.04f / 60.0f;
  time += deltaTime;

  forceApplier_->applyForce(*block_, time);
  world_->Step(deltaTime, 8, 3);

  blockManager_->update(deltaTime);

  for (auto it = hearts.begin(); it != hearts.end();)
  {
    (*it)->update(deltaTime);
    if ((*it)->isAnimationComplete())
    {
      std::cout << "Animação completa para o coração: " << *it << std::endl;
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
  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  world_->DebugDraw();

  std::string scoreText = "Pontuacao: " + std::to_string(blockManager_->getScore());
  std::string scoreTextB = "BLock: " + std::to_string(blockManager_->getblock());
  std::string scoreTextL = "Last: " + std::to_string(blockManager_->getlast());
  renderer->drawText(scoreText.c_str(), 20, 120, 255, 255, 255, 255);
  renderer->drawText(scoreTextB.c_str(), 20, 140, 255, 255, 255, 255);
  renderer->drawText(scoreTextL.c_str(), 20, 160, 255, 255, 255, 255);



  baseBlock->render(renderer);
  blockTest_->render(renderer);

  for (const auto &block : blocks)
  {
    block->render(renderer);
  }

  int x = 20;
  for (const auto &heart : hearts)
  {
    heart->render(x, 20);
    x += 50;
  }

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
  delete blockTest_;
}

void Game::loseLife()
{
  if (lives > 0 && !hearts.empty())
  {
    Heart *heart = hearts.back();
    heart->loseHeart();
    --lives;
  }
}
