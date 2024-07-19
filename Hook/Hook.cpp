#include "Hook.h"
#include <iostream>

Hook::Hook(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(pixelsToMeters(HOOK_XPOSITION),pixelsToMeters(HOOK_YPOSITION));
    bodyDef.angle = 0;

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(HOOK_WIDTH)/2.0f, pixelsToMeters(HOOK_HEIGHT)/2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.2f;

    body->CreateFixture(&fixtureDef);

    color = {0, 255, 0};

}

void Hook::render(Renderer* renderer) const {
    
    b2Vec2 position = body->GetPosition();
    int x = static_cast<int>(metersToPixels(position.x) - HOOK_WIDTH/2);
    int y = static_cast<int>(metersToPixels(position.y) - HOOK_HEIGHT/2);
      

    renderer->setDrawColor(color.r, color.g, color.b, color.a);
    renderer->drawRect(x, y, HOOK_WIDTH, HOOK_HEIGHT);
}
