// hook2.h

#ifndef HOOK_H
#define HOOK_H

#include "../utils/Constants.h"
#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../utils/Utils.h"
#include "Line.h"
#include "Block.h"

class Hook{
    public:
    Hook(b2World* world_, b2Vec2 anchorPosition);

    void render(PortRender* renderer) const;
    void applyInitialForce(float time);
    b2Body* getBody() const { return body; }
    b2World* getWorld() const { return world_; }
    
protected:
    b2World* world_;
    b2Body* body;
    Color color;

    float frequency;
    float amplitude;
    float phase;
};

#endif