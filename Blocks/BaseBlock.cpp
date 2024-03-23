#include "BaseBlock.h"
#include "../Constants.h"

BaseBlock::BaseBlock(b2World* world_, float x, float y, float width, float height, uint8_t r, uint8_t g, uint8_t b) 
            : Block(world_, x, y, width, height, r, g, b) {

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(x, y);     // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width/2, height/2); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f;     // Densidade
    fixtureDef.friction = 0.0f;    // Coeficiente de fricção
    fixtureDef.restitution = 0.0f; // Coeficiente de restituição

    // Adicione a forma ao corpo
    body->CreateFixture(&fixtureDef);


    cor = { r, g, b };
}
