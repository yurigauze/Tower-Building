// baseblock.h
#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../render/Camera.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "AbstractObject.h"

class BaseBlock : public AbstractObject {
public:
  BaseBlock(b2World* world, PortRender* renderer);

  void render(PortRender *renderer, Camera &camera) const override;

  b2Body* getBody() const override { return body; }

protected:
};
#endif
