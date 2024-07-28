// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"

class Block {
public:
  Block(b2World *world, b2Vec2 anchorPosition);

  void render(PortRender *renderer) const;
  void release();
  void applyTorque(float torque);
  b2Body *getBody() const { return body; }
  bool getIsReleased() const { return isReleased; }

protected:
  b2World *world_;
  b2Body *body;
  b2Joint *joint;
  bool isReleased;
  Color Bcolor;

  float frequency;
  float amplitude;
  float phase;
};

#endif
