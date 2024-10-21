#include "Game.h"
#include "models/rules/BlockManager.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <list>
#include <stdexcept>
#include <algorithm>

Game::Game(const char *title, int xpos, int ypos, int width, int height,
           bool fullscreen, PortRender *renderer, EventHandler *eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true),
      lives(3), isBlockOnHookActive(true)
{

  camera = new Camera(WIDTH, HEIGHT, 300);
  b2Vec2 gravity(0.0f, 9.81f);
  world_ = new b2World(gravity);
  debugDraw = new DebugDraw(renderer);
  world_->SetDebugDraw(debugDraw);

  contactListener_ = new ContactListener();
  world_->SetContactListener(contactListener_);

  uint32 flags = 0;
  flags |= b2Draw::e_shapeBit;
  debugDraw->SetFlags(flags);

  controller_ =
      new Controller(eventHandler, world_, block_, blocks, isRunning, renderer, blockTest_, camera, blockManager_);

  b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
  block_ = new Block(world_, renderer, anchorPosition);
  // blocks.push_back(block_);
  baseBlock = new BaseBlock(world_, renderer);

  forceApplier_ = new ForceApplier(5.0f, 1.0f, 0.0f);

  for (int i = 0; i < lives; ++i)
  {
    Heart *heart = new Heart(renderer, "heart", "assets/heart-explode.png", 10);
    hearts.push_back(heart);
  }

  blockManager_ = new BlockManager(world_, block_, blocks, 1000.0f, hearts, this, contactListener_);

  if (!renderer->loadFont("src/font/ARIAL.TTF", 24))
  {
    throw std::runtime_error("Failed to initialize font in SDLRenderer");
  }
}

void Game::handleEvents() { controller_->handleEvents(); }

void Game::update()
{
  static float time = 0.0f;
  float deltaTime = 0.020f / 60.0f;
  time += deltaTime;

  forceApplier_->applyForce(*block_, time);
  world_->Step(deltaTime, 8, 3);

  blockManager_->update(deltaTime);

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
  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  std::string scoreText = "Pontuacao: " + std::to_string(blockManager_->getScore());
  renderer->drawText(scoreText.c_str(), 20, 120, 255, 255, 255, 255);

  baseBlock->render(renderer, *camera);

  for (auto it = blocks.begin(); it != blocks.end();)
  {
    Block *block = *it;
    if (block)
    {
      std::cerr << "Tentei renderizar: " << block << std::endl;
      block->render(renderer, *camera);
      ++it; // Avance apenas se o bloco é válido
    }
    else
    {
      std::cerr << "Encontrado um bloco nulo na lista de blocos!" << std::endl;
      it = blocks.erase(it); // Remova o bloco nulo da lista
    }
  }

  if (block_)
  {
    block_->render(renderer, *camera);
  }

  // Renderiza os corações
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
  delete camera;
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

Block *Game::createNewBlock()
{
  if (block_)
  {
    std::cerr << "O bloco atual ainda existe, mas não será adicionado à lista." << std::endl;
  }

  b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
  Block *newBlock = new Block(world_, renderer, anchorPosition);
  block_ = newBlock;
  return newBlock;
}

void Game::destroyBlock(Block *block)
{
  if (block)
  {
    std::cerr << "Destruindo bloco em: " << block << std::endl;
    blocks.remove(block);
    world_->DestroyBody(block->getBody());
    delete block;
    std::cerr << "Bloco destruído e memória liberada." << std::endl;
  }
  else
  {
    std::cerr << "Tentativa de destruir um bloco nulo!" << std::endl;
  }
}

void Game::addBlockToList(Block* block)
{
    if (block)
    {
        blocks.push_back(block);
        std::cerr << "Bloco adicionado à lista: " << block << std::endl;
    }
    else
    {
        std::cerr << "Tentativa de adicionar um bloco nulo à lista!" << std::endl;
    }
}
