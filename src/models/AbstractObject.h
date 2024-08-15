#ifndef ABSTRACTOBJECT_H
#define ABSTRACTOBJECT_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"

class AbstractObject {
public:
    AbstractObject(b2World* world) : world_(world), body(nullptr) {}

       virtual ~AbstractObject() {}

    virtual void render(PortRender* renderer) const = 0;
    virtual b2Body* getBody() const { return body; }
    virtual void applyTorque(float torque) {} 

protected:
    b2World* world_;
    b2Body* body;
    Color color;
};

#endif
