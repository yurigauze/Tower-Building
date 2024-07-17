#include "Block.h"
#include "../Constants.h"
#include <iostream>

Block::Block(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(B_XPOSITION, B_YPOSITION); 
    bodyDef.angle = 0;   // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(BLOCK_WIDTH/2, BLOCK_HEIGHT/2); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f;     // Densidade
    fixtureDef.friction = 0.5f;    // Coeficiente de fricção
    fixtureDef.restitution = 0.0f; // Coeficiente de restituição

    // Adicione a forma ao corpo
    body->CreateFixture(&fixtureDef);

    color = { 255, 255, 255 };
}

void Block::render(Renderer* renderer) const {
    // Obter a posição do corpo físico e ajustá-la para renderização
    b2Vec2 position = body->GetPosition();

    int x = static_cast<int>(position.x - BLOCK_WIDTH / 2);
    int y = static_cast<int>(position.y - BLOCK_HEIGHT / 2);

    renderer->drawRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
    renderer->setDrawColor(color.r, color.g, color.b, color.a);
}

