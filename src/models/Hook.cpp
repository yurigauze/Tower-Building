#include "Hook.h"
#include <iostream>

Hook::Hook(b2World* world_, b2Vec2 anchorPosition){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pixelsToMeters(HOOK_XPOSITION),pixelsToMeters(HOOK_YPOSITION));
    bodyDef.angle = 0;
    bodyDef.angularDamping = 0.1f; 

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(HOOK_WIDTH)/2.0f, pixelsToMeters(HOOK_HEIGHT)/2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.2f;
    fixtureDef.restitution = 100.0f;

    body->CreateFixture(&fixtureDef);

    // Corpo onde fixo no espaço
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

    b2Joint* joint = world_->CreateJoint(&jointDef);

    color = {0, 255, 0};

}

void Hook::applyInitialForce(float time) {
    float torque = amplitude * std::sin(frequency * time + phase);
    body->ApplyTorque(torque, true);
}


void Hook::render(PortRender* renderer) const {
    
    b2Vec2 position = body->GetPosition();
    int x = static_cast<int>(metersToPixels(position.x) - HOOK_WIDTH/2);
    int y = static_cast<int>(metersToPixels(position.y) - HOOK_HEIGHT/2);
        
    //std::cout <<x<<std::endl;
    //std::cout <<y<<std::endl;

    renderer->setDrawColor(color.r, color.g, color.b, color.a);
    renderer->drawRect(x, y, HOOK_WIDTH, HOOK_HEIGHT);
}


