#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include "../Constants.h"
#include "../box2d/box2d.h"
#include "Block.h"
#include "../Render/Renderer.h"

class BaseBlock : public Block {
public:
    BaseBlock(b2World* world, float x, float y, int r, int g, int b);

    void render(Renderer* renderer) const override {

        b2Vec2 position = getBody()->GetPosition();
        int renderX = static_cast<int>(position.x);
        int renderY = static_cast<int>(position.y);
        renderer->setDrawColor(color.r, color.g, color.b, color.a);
        renderer->drawRect(renderX, renderY, BLOCK_WIDTH, BLOCK_HEIGHT);
    }
 
};
#endif
