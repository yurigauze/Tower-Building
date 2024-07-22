#include "Block.h"
#include "../Game.h"
#include <iostream>

Block::Block(b2World* world_, b2Vec2 anchorPosition)
    : world_(world_), isReleased(false){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;  // Tipo de corpo dinâmico
    bodyDef.position.Set(pixelsToMeters(B_XPOSITION), pixelsToMeters(B_YPOSITION)); 
    bodyDef.angle = 0;   // Posição do corpo
    bodyDef.angularDamping = 0.1f; 

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(BLOCK_WIDTH)/2.0f, pixelsToMeters(BLOCK_HEIGHT)/2.0f); // Define um retângulo

    // Defina as propriedades do corpo físico
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 0.0f;
    fixtureDef.restitution = 0.0f;

    body->CreateFixture(&fixtureDef);

    b2BodyDef anchorBodyDef;
    anchorBodyDef.type = b2_staticBody;
    anchorBodyDef.position.Set(pixelsToMeters(anchorPosition.x), pixelsToMeters(anchorPosition.y));
    b2Body* anchorBody = world_->CreateBody(&anchorBodyDef);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = anchorBody; // Corpo fixo do mundo, o âncora
    jointDef.bodyB = body; // Corpo dinâmico
    jointDef.localAnchorA.SetZero();
    jointDef.localAnchorB.Set(0,pixelsToMeters(200));
    jointDef.collideConnected = false;

    //ajuste de angulo de balanço
    jointDef.lowerAngle = b2_pi / 2.0f; // 90º em radianos
    jointDef.upperAngle = 3.0f * b2_pi / 2.0f; //270º
    jointDef.enableLimit = true;

    joint = world_->CreateJoint(&jointDef);

    Bcolor = {0, 255, 0};
}

void Block::release() {
    if (joint) {
        // Define o ângulo do corpo para 0 (ou qualquer outro ângulo desejado)
        body->SetTransform(body->GetPosition(), 0.0f);

        // Remove o joint para soltar o bloco
        body->GetWorld()->DestroyJoint(joint);
        joint = nullptr;

        // Define a velocidade linear para garantir que não haja movimento lateral
        b2Vec2 velocity = body->GetLinearVelocity();
        body->SetLinearVelocity(b2Vec2(0, velocity.y));

        // Define a velocidade angular para garantir que não haja rotação
        body->SetAngularVelocity(0.0f);

        // Garante que o corpo está "acordado" para simular física
        body->SetAwake(true);

        isReleased = true; // Marca o bloco como solto
    }
}


void Block::applyInitialForce(float time) {
    float torque = amplitude * std::sin(frequency * time + phase);
    body->ApplyTorque(torque, true);
}

void Block::render(Renderer* renderer) const {

    b2Vec2 position = body->GetPosition();

    int x = static_cast<int>(metersToPixels(position.x) - BLOCK_WIDTH / 2);
    int y = static_cast<int>(metersToPixels(position.y) - BLOCK_HEIGHT / 2);

    renderer->setDrawColor(Bcolor.r, Bcolor.g, Bcolor.b, Bcolor.a);
    renderer->drawRect(x, y, BLOCK_WIDTH, BLOCK_HEIGHT);
}

