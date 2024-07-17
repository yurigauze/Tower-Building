#include "BaseBlock.h"
#include "../Constants.h"

BaseBlock::BaseBlock(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(BB_XPOSITION, BB_YPOSITION);     // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(BLOCK_WIDTH/2, BLOCK_HEIGHT/2); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f;     // Densidade
    fixtureDef.friction = 0.0f;    // Coeficiente de fricção
    fixtureDef.restitution = 0.0f; // Coeficiente de restituição

    // Adicione a forma ao corpo
    body->CreateFixture(&fixtureDef);


    color = { 255, 255, 25 };
}

void BaseBlock::render(Renderer* renderer) const {
    
    b2Vec2 position = body->GetPosition();

    int renderX = static_cast<int>(position.x - BLOCK_WIDTH/2);
    int renderY = static_cast<int>(position.y - BLOCK_HEIGHT/2);

    renderer->setDrawColor(color.r, color.g, color.b, color.a);
    renderer->drawRect(renderX, renderY, BLOCK_WIDTH, BLOCK_HEIGHT);
}

