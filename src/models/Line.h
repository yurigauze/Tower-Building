// line2.h
#ifndef LINE_H
#define LINE_H

#include "../utils/Utils.h"
#include "../utils/Constants.h"
#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"


class Line {
public:
    Line(b2World* world_);

    void render(PortRender* renderer) const;
   

    b2Body* getBody() const;
    
protected:
    b2Body* body;
    Color color;
    b2DistanceJoint* joint;
};

#endif

