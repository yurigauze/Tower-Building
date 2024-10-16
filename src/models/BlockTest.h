#ifndef BLOCK_TEST_H
#define BLOCK_TEST_H

#include "../include/box2d/box2d.h"
#include "../render/PortRender.h"
#include "../utils/Constants.h"
#include "../utils/Utils.h"
#include "AbstractObject.h"

class BlockTest : public AbstractObject
{
public:
    BlockTest(b2World *world, PortRender *renderer, b2Vec2 position);

    void render(PortRender *renderer, Camera &camera) const override;

private:
};

#endif // BLOCK_TEST_H
