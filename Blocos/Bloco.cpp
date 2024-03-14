#include "Bloco.h"

Bloco::Bloco(b2World* world_, float width, float height, float density,
             float friction, float restitution, b2Vec2 position,
             uint8_t r, uint8_t g, uint8_t b) {

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Tipo de corpo dinâmico
    bodyDef.position = position;     // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width / 2.0f, height / 2.0f); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = density;         // Densidade
    fixtureDef.friction = friction;       // Coeficiente de fricção
    fixtureDef.restitution = restitution; // Coeficiente de restituição

    // Adicione a forma ao corpo
    body->CreateFixture(&fixtureDef);


    cor = { r, g, b };
}

void Bloco::renderizar(SDL_Renderer* renderer) const {
    // Obter a posição do corpo físico e ajustá-la para renderização
    b2Vec2 position = body->GetPosition();
    int x = static_cast<int>(position.x - BLOCO_WIDTH / 2.0f);
    int y = static_cast<int>(position.y - BLOCO_HEIGHT / 2.0f);

    SDL_Rect rect = { x, y, BLOCO_WIDTH, BLOCO_HEIGHT };
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

