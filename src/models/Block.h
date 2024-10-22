#ifndef BLOCK_H
#define BLOCK_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../render/Camera.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "AbstractObject.h"
#include "rules/ContactListener.h"
#include <iostream>

class Block : public AbstractObject
{
public:
  Block(b2World *world, PortRender *renderer, b2Vec2 anchorPosition, Camera* camera);

  void render(PortRender *renderer, Camera &camera) const override;
  void release();
  void applyTorque(float torque);
  bool getIsReleased() const { return isReleased; }
  bool isPositioned;

  bool isInContactWithAnotherBlock(ContactListener *contactListener);

  void markAsPositioned(Camera* camera);

protected:
  b2Joint *joint;
  bool isReleased;
  float frequency;
  float amplitude;
  float phase;
};

#endif
