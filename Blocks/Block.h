// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "../Utils/Utils.h"
#include "../Constants.h"  
#include "../box2d/box2d.h"
#include "../Render/Renderer.h"


class Block {
public:
    Block(b2World* world_, b2Vec2 anchorPosition);

    void render(Renderer* renderer) const;
    void applyInitialForce(float time);
    void release();
    b2Body* getBody() const { return body; }
    bool getIsReleased() const { return isReleased; }
    
protected:
    b2World* world_;
    b2Body* body;
    b2Joint* joint;
    bool isReleased; 
    Color Bcolor;

    float frequency;
    float amplitude;
    float phase;
};

#endif

