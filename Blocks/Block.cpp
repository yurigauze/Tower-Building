#include "Block.h"
#include <iostream>

Block::Block(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(pixelsToMeters(B_XPOSITION), pixelsToMeters(B_YPOSITION)); 
    bodyDef.angle = 0;   // Posição do corpo
    body = world_->CreateBody(&bodyDef);


    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(BLOCK_WIDTH / 2.0f), pixelsToMeters(BLOCK_HEIGHT / 2.0f)); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 0.01f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.0f;

    body->CreateFixture(&fixtureDef);

    Bcolor = { 255, 0, 0 };
}

void Block::render(Renderer* renderer) const {

    b2Vec2 position = body->GetPosition();

    int x = static_cast<int>(metersToPixels(position.x) - BLOCK_WIDTH / 2);
    int y = static_cast<int>(metersToPixels(position.y) - BLOCK_HEIGHT / 2);

    renderer->setDrawColor(Bcolor.r, Bcolor.g, Bcolor.b, Bcolor.a);
    renderer->drawRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT);

}

