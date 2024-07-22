#include "BaseBlock.h"
#include <iostream>

BaseBlock::BaseBlock(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(pixelsToMeters(BB_XPOSITION), pixelsToMeters(BB_YPOSITION));     // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(BLOCK_WIDTH)/2.0f, pixelsToMeters(BLOCK_HEIGHT)/2.0f); 

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f;     // Densidade
    fixtureDef.friction = 0.0f;    // Coeficiente de fricção
    fixtureDef.restitution = 0.0f; // Coeficiente de restituição

    // Adicione a forma ao corpo
    body->CreateFixture(&fixtureDef);


    color = { 0, 255, 0 };
}

void BaseBlock::render(Renderer* renderer) const {
    
    b2Vec2 position = body->GetPosition();

    int renderX = static_cast<int>(metersToPixels(position.x) - BLOCK_WIDTH / 2);
    int renderY = static_cast<int>(metersToPixels(position.y) - BLOCK_HEIGHT / 2);

    renderer->setDrawColor(color.r, color.g, color.b, color.a);
    renderer->drawRect(renderX, renderY, BLOCK_WIDTH, BLOCK_HEIGHT);
}