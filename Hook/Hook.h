// hook2.h

#ifndef HOOK_H
#define HOOK_H

#include "../Constants.h"
#include "../box2d/box2d.h"
#include "../Render/Renderer.h"
#include "../Utils/Utils.h"
#include "Line.h"
#include "../Blocks/Block.h"

class Hook{
    public:
    Hook(b2World* world_, b2Vec2 anchorPosition);

    void render(Renderer* renderer) const;
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