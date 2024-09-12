#include "Game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <fstream>
#include <list>
#include <stdexcept>

Game::Game(const char *title, int xpos, int ypos, int width, int height,
           bool fullscreen, PortRender *renderer, EventHandler *eventHandler)
    : renderer(renderer), eventHandler(eventHandler), isRunning(true),
      lives(3) { // Initialize lives here

  b2Vec2 gravity(0.0f, 9.81f);
  world_ = new b2World(gravity);
  debugDraw = new DebugDraw(renderer);
  world_->SetDebugDraw(debugDraw);

  uint32 flags = 0;
  flags |= b2Draw::e_shapeBit;
  debugDraw->SetFlags(flags);

  controller_ =
      new Controller(eventHandler, world_, block_, blocks, isRunning, renderer);

  b2Vec2 anchorPosition(AnchorPositionX, AnchorPositionY);
  block_ = new Block(world_, renderer, anchorPosition);
  blocks.push_back(block_);
  baseBlock = new BaseBlock(world_, renderer);

  forceApplier_ = new ForceApplier(5.0f, 1.0f, 0.0f);
  blockManager_ = new BlockManager(world_, blocks, 1000.0f, hearts);

  if (!renderer->loadFont("src/font/ARIAL.TTF", 24)) {
    throw std::runtime_error("Failed to initialize font in SDLRenderer");
  }

  for (int i = 0; i < lives; ++i) {
    hearts.emplace_back(
        new Heart(renderer, "heart", "assets/heart-explode.png", 10));
  }
}

void Game::handleEvents() { controller_->handleEvents(); }

void Game::update() {
  static float time = 0.0f;
  float deltaTime = 0.10f / 60.0f;
  time += deltaTime;

  forceApplier_->applyForce(*block_, time);
  world_->Step(deltaTime, 8, 3);

  blockManager_->update(deltaTime);

  for (auto &heart : hearts) {
    heart->update(deltaTime);
    if (heart->isAnimationComplete()) {
      // Opcional: Remover ou lidar com o coração quando a animação terminar
    }
  }
}

void Game::render() {
  renderer->setDrawColor(0, 0, 0, 255);
  renderer->clear();

  world_->DebugDraw();

  renderer->drawText("Deu Certo", 0, 200, 0, 0, 255, 255);
  baseBlock->render(renderer);

  for (const auto &block : blocks) {
    block->render(renderer);
  }

  int x = 50;
  for (const auto &heart : hearts) {
    heart->render(x, 50);
    x += 100;
  }

  renderer->present();
}

void Game::clean() {
  for (auto block : blocks) {
    world_->DestroyBody(block->getBody());
    delete block;
  }
  blocks.clear();

  for (auto heart : hearts) {
    delete heart;
  }
  hearts.clear();

  delete baseBlock;
  delete world_;
  delete debugDraw;
  delete forceApplier_;
  delete blockManager_;
}

void Game::loseLife() {
  if (lives > 0) {
    hearts[lives - 1]->loseHeart();
    --lives;
  }
}
