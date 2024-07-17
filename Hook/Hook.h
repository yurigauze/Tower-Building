// hook.h
#ifndef HOOK_H
#define HOOK_H

#include "../Constants.h"
#include "../box2d/box2d.h"
#include "Line.h"   
#include "../Render/Renderer.h"
#include "../Utils/Utils.h"

class Hook {
public:
    Hook(b2World* world_);

    void render(Renderer* renderer) const;

    b2Body* getBody() const { return body; }
    void setJointWithLine(b2RevoluteJoint* joint);
    void setMotorSpeed(float speed);
    
protected:
    b2Body* tipBody;
    Line* line; //Linha
    b2RevoluteJoint* jointWithLine;
    b2Body* body; // Corpo físico do bloco
    Color color;
};

#endif

