#ifndef HEART_H
#define HEART_H

#include "../../render/sprites/Sprites.h"
#include "../../Game.h"
#include <iostream>

class Heart
{
public:
  Heart(PortRender *renderer, const std::string &textureId,
        const std::string &texturePath, int totalFrames, Game *game)
      : isLost(false), removeAfterAnimation(false), renderer(renderer),
        heartSprite(nullptr), game(game)
  {
    heartSprite = new Sprites(textureId, texturePath, renderer, 127, 125,
                              totalFrames, 0.1f);
  }

  ~Heart() { delete heartSprite; }

  void update(float deltaTime)
  {
    if (heartSprite && isLost)
    {
      heartSprite->update(deltaTime);

      if (heartSprite->isLastFrame())
      {
        removeAfterAnimation = true;
        if (game)
        {
          game->loseLife();
        }
      }
    }
  }

  void render(int x, int y)
  {
    int reducedWidth = 64;
    int reducedHeight = 64;

    if (heartSprite)
    {
      if (isLost)
      {
        heartSprite->render(renderer->getRenderer(), x, y, reducedWidth, reducedHeight);
      }
      else
      {
        heartSprite->renderFullImage(renderer->getRenderer(), x, y, reducedWidth, reducedHeight);
      }
    }
  }

  void loseHeart()
  {
    if (!isLost)
    {
      isLost = true;
      heartSprite->reset();
      removeAfterAnimation = false;
    }
  }

  bool isAnimationComplete() const { return removeAfterAnimation; }

  bool isLostHeart() const { return isLost; }

private:
  bool isLost;
  bool removeAfterAnimation;
  PortRender *renderer;
  Sprites *heartSprite;
  Game *game;
};

#endif // HEART_H
