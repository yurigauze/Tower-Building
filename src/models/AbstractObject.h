#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../render/sprites/Sprites.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"

class AbstractObject {
public:
  AbstractObject(b2World *world, PortRender *renderer)
      : renderer(renderer), sprites(nullptr), world_(world), body(nullptr) {}

  virtual ~AbstractObject() { delete sprites; }

  virtual void render(PortRender *renderer) const = 0;
  virtual b2Body *getBody() const { return body; }
  virtual void applyTorque(float torque) {}

protected:
  PortRender *renderer;
  Sprites *sprites;
  b2World *world_;
  b2Body *body;
  Color color;
};

#endif
