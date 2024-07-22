// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "../Utils/Utils.h"
#include "../Constants.h"
#include "../box2d/box2d.h"
#include "../Render/Renderer.h"

class Hook;


class Block {
public:
    Block(b2World* world_);

    void render(Renderer* renderer) const;

    b2Body* getBody() const { return body; }
    
protected:
    b2World* world_;
    b2Body* body; // Corpo físico do bloco
    Color Bcolor; // Propriedades de cor do bloco
};

#endif

