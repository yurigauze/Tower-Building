// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "AbstractObject.h"

class Block : public AbstractObject{
public:
  Block(b2World *world, b2Vec2 anchorPosition);

  void render(PortRender *renderer) const override;
  void release();
  void applyTorque(float torque);
  bool getIsReleased() const { return isReleased; }

protected:
    b2Joint* joint;
    bool isReleased;

    float frequency;
    float amplitude;
    float phase;
};

#endif
