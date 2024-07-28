// baseblock.h
#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "../utils/Utils.h"
#include "../utils/Constants.h"
#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"

class BaseBlock{
public:
    BaseBlock(b2World* world);

    void render(PortRender* renderer) const;

    b2Body* getBody() const { return body ;}
    

protected:
    b2Body* body;
    Color color;
};
#endif
