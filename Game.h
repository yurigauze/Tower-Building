#ifndef GAME_H
#define GAME_H

#include "src/DebugDraw/DebugDraw.h"
#include "src/controller/Controller.h"
#include "src/include/box2d/box2d.h"
#include "src/models/BaseBlock.h"
#include "src/models/Block.h"
#include "src/render/EventHandler.h"
#include "src/render/PortRender.h"
#include "src/utils/Constants.h"
#include "src/models/rules/ForceApplier.h"
#include "src/models/rules/BlockManager.h"
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
};

#endif // GAME_H
