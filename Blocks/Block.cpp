#include "Block.h"
#include "../Constants.h"
#include <iostream>

Block::Block(b2World* world_, float x, float y, float width, float height, uint8_t r, uint8_t g, uint8_t b) {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(x, y); 
    bodyDef.angle = 0;   // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width/2, height/2); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f;     // Densidade
    fixtureDef.friction = 0.5f;    // Coeficiente de fricção
    fixtureDef.restitution = 0.0f; // Coeficiente de restituição

    // Adicione a forma ao corpo
    body->CreateFixture(&fixtureDef);

    cor = { r, g, b };
}

void Block::render(SDL_Renderer* renderer) const {
    // Obter a posição do corpo físico e ajustá-la para renderização
    b2Vec2 position = body->GetPosition();

    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    SDL_Rect rect = { x - 70, y, BLOCK_WIDTH, BLOCK_HEIGHT};
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

