#include "Game.h"
#include <list>

Game::Game(const char *title, int xpos, int ypos, int width, int height,
           bool fullscreen, PortRender *renderer, EventHandler *eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true) {

  b2Vec2 gravity(0.0f, 9.81f);
  world_ = new b2World(gravity);
  debugDraw = new DebugDraw(renderer);
  world_->SetDebugDraw(debugDraw);

  uint32 flags = 0;
  flags |= b2Draw::e_shapeBit;
  debugDraw->SetFlags(flags);

  controller_ = new Controller(eventHandler, world_, block_, blocks, isRunning);
  b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
  block_ = new Block(world_, anchorPosition);
  blocks.push_back(block_);
  baseBlock = new BaseBlock(world_);

  forceApplier_ = new ForceApplier(5.0f, 1.0f, 0.0f);
  blockManager_ = new BlockManager(world_, blocks, 1000.0f);
}

void Game::handleEvents() { 
  controller_->handleEvents(); 
  
}

void Game::update() {

  static float time = 0.0f;
  float deltaTime = 0.10f / 60.0f;
  time += deltaTime;

  forceApplier_->applyForce(*block_, time);
  world_->Step(deltaTime, 8, 3);

  blockManager_->update(deltaTime);
}

void Game::render() {

  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  world_->DebugDraw();
  renderer->present();
}

void Game::clean() {
  for (auto block : blocks) {
    world_->DestroyBody(block->getBody());
    delete block;
  }
  blocks.clear();

  delete world_;
  delete debugDraw;
  delete forceApplier_;
}