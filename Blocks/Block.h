// block.h
#ifndef BLOCK_H
#define BLOCK_H

#include <SDL2/SDL.h>
#include "../Constants.h"
#include "../box2d/box2d.h"


class Block {
public:
    Block(b2World* world_, float x, float y, float width, float height, uint8_t r, uint8_t g, uint8_t b);

    void render(SDL_Renderer* renderer) const;

    b2Body* getBody() const { return body; }
    
protected:
    b2Body* body; // Corpo físico do bloco
    SDL_Color cor;// Propriedades de cor do bloco
};

#endif

