#ifndef GAME_H
#define GAME_H

#include "DebugDraw/DebugDraw.h"
#include "controller/Controller.h"
#include "include/box2d/box2d.h"
#include "models/BaseBlock.h"
#include "models/Block.h"
#include "render/EventHandler.h"
#include "render/PortRender.h"
#include "render/SDLRenderer.h" 
#include "utils/Constants.h"
#include "models/rules/ForceApplier.h"
#include "models/rules/BlockManager.h"
#include "render/sprites/TextureManager.h"

#include <SDL2/SDL.h>
#include <iostream>
#include <list>

class Game {
public:
  Game(const char *title, int xpos, int ypos, int width, int height,
       bool fullscreen, PortRender *renderer, EventHandler *eventHandler);

  void handleEvents();
  void update();
  void render();
  void clean();

  bool running() const { return isRunning; }
  std::list<Block *> &getBlocks() { return blocks; }

private:
  ForceApplier *forceApplier_;
  Controller *controller_;
  PortRender *renderer;
  BaseBlock *baseBlock;
  EventHandler *eventHandler;
  std::list<Block *> blocks;
  b2World *world_;
  Block *block_;
  DebugDraw *debugDraw;
  bool isRunning;
  BlockManager *blockManager_;
  TextureManager* textureManager;
};

#endif // GAME_H