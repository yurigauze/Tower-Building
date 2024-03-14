// bloco.h
#ifndef BLOCO_H
#define BLOCO_H

#include <SDL2/SDL.h>
#include "../Constants.h"
#include "../box2d/box2d.h"


class Bloco {
public:
    Bloco(b2World* world_, float width, float height, float density,
          float friction, float restitution, b2Vec2 position, uint8_t r, uint8_t g, uint8_t b);

    void renderizar(SDL_Renderer* renderer) const;

        
private:
    b2Body* body; // Corpo físico do bloco
    SDL_Color cor;// Propriedades de cor do bloco
};

#endif

