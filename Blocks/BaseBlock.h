#ifndef BASEBLOCK_H
#define BASEBLOCK_H

#include <SDL2/SDL.h>
#include "../Constants.h"
#include "../box2d/box2d.h"
#include "Block.h"

class BaseBlock : public Block {
public:
    BaseBlock(b2World* world_, float x, float y, float width, float height, uint8_t r, uint8_t g, uint8_t b);

};
#endif
