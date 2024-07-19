// hook2.h

#ifndef HOOK_H
#define HOOK_H

#include "../Constants.h"
#include "../box2d/box2d.h"
#include "Line.h"   
#include "../Render/Renderer.h"
#include "../Utils/Utils.h"

class Hook{
    public:
    Hook(b2World* world_);

void render(Renderer* renderer) const;

    b2Body* getBody() const { return body; }
    
protected:
    b2Body* body;
    Color color;
};

#endif