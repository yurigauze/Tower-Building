#ifndef GAME_H
#define GAME_H

#include "DebugDraw/DebugDraw.h"
#include "controller/Controller.h"
#include "include/box2d/box2d.h"
#include "models/BaseBlock.h"
#include "models/BlockTest.h"
#include "models/Block.h"
#include "render/EventHandler.h"
#include "render/PortRender.h"
#include "render/SDLRenderer.h" 
#include "utils/Constants.h"
#include "models/rules/ForceApplier.h"
#include "models/objects/Heart.h"
#include "models/rules/ContactListener.h"
#include "render/camera/Camera.h" 


#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <list>

class BlockManager;

class Game {
  
public:
  Game(const char *title, int xpos, int ypos, int width, int height,
       bool fullscreen, PortRender *renderer, EventHandler *eventHandler);

  void handleEvents();
  void update();
  void render();
  void clean();
  void loseLife();

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
  BlockTest *blockTest_;
  DebugDraw *debugDraw;
  bool isRunning;
  BlockManager *blockManager_;
  std::list<Heart *> hearts;
  int lives;
  ContactListener *contactListener_;
  Camera *camera;
};

#endif // GAME_H
