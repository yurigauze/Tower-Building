// line2.h
#ifndef LINE_H
#define LINE_H

#include "../Utils/Utils.h"
#include "../Constants.h"
#include "../box2d/box2d.h"
#include "../Render/Renderer.h"


class Line {
public:
    Line(b2World* world_);

    void render(Renderer* renderer) const;
   

    b2Body* getBody() const;
    
protected:
    b2Body* body;
    Color color;
    b2DistanceJoint* joint;
};

#endif

