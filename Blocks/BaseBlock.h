#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "../Constants.h"
#include "../box2d/box2d.h"
#include "Block.h"
#include "../Render/Renderer.h"

class BaseBlock{
public:
    BaseBlock(b2World* world);

    void render(Renderer* renderer) const;

    b2Body* getBody() const { return body ;}
    

protected:
    b2Body* body;
    Color color;
};
#endif
