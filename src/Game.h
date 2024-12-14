#ifndef GAME_H
#define GAME_H

#include "DebugDraw/DebugDraw.h"
#include "include/box2d/box2d.h"
#include "models/BaseBlock.h"
#include "models/BlockTest.h"
#include "models/Block.h"
#include "render/EventHandler.h"
#include "render/PortRender.h"
#include "render/SDLRenderer.h"
#include "utils/Constants.h"
#include "models/rules/ForceApplier.h"
#include "models/rules/ContactListener.h"
#include "render/Camera.h"
#include "models/objects/Background.h"
#include "models/objects/PauseBackground.h"
#include "render/screens/EndBackground.h"
#include "render/screens/InitialGame.h"
#include "render/screens/CreditGame.h"
#include "render/sprites/ClickableSprite.h"

#include <SDL2/SDL.h>
#include <vector>
#include <iostream>
#include <list>

class BlockManager;
class Controller;
class Heart;

class Game
{

public:
  Game(const char *title, int xpos, int ypos, int width, int height,
       bool fullscreen, PortRender *renderer, EventHandler *eventHandler);

  void handleEvents();
  void update();
  void render();
  void clean();
  void loseLife();

  void togglePause();
  void toggleInitial();
  bool isPaused() const;

  bool isGameOver() { return isGameOver_; }
  bool isGameStarted() { return isGameStarted_;}

  void renderStartScreen();
  void renderPauseScreen();
  void renderEndgameScreen();
  void renderCreditScreen();

  void endgame();

  void resetGame();
  void startNewGame();

  bool running() const { return isRunning; }
  std::list<Block *> &getBlocks() { return blocks; }
  ClickableSprite* getPauseMenu() { return pauseMenu_; }

private:
  bool paused = false;
  bool isGameOver_;
  bool isGameStarted_ = false; 
  

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
  Heart *heart;
  std::list<Heart *> hearts;
  int lives;
  ContactListener *contactListener_;
  Camera *camera;
  Background *background;
  PauseBackground *pauseBackground;
  EndBackground *endBackground_;
  InitialGame *initialGame_;
  CreditGame *creditGame_;
  ClickableSprite* pauseMenu_;


};

#endif // GAME_H
