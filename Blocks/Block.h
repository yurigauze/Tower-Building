// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include "../Utils/Utils.h"
#include "../Constants.h"
#include "../box2d/box2d.h"
#include "../Render/Renderer.h"


class Block {
public:
    Block(b2World* world, float x, float y, int r, int g, int b);

    void render(Renderer* renderer) const;

    b2Body* getBody() const { return body; }
    
protected:
    b2Body* body; // Corpo físico do bloco
    Color color; // Propriedades de cor do bloco
};

#endif

