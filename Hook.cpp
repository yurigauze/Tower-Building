#include "Hook.h"

Hook::Hook(b2World* world_, float x, float y, float width, float height){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x,y);
    bodyDef.angle =0;

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(width/2, height/2);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.2f;

    body->CreateFixture(&fixtureDef);

    cor = {0, 255, 0};

    b2BodyDef anchorDef;
    anchorDef.type = b2_staticBody;
    anchorDef.position.Set(x, y - height/2);

    b2Body* anchorBody = world_->CreateBody(&anchorDef);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = anchorBody;
    jointDef.bodyB = body;
    jointDef.localAnchorA.Set(0,0);
    jointDef.localAnchorB.Set(0, height/2);
    jointDef.enableMotor = true;
    jointDef.maxMotorTorque = 1000.0f;

    world_->CreateJoint(&jointDef);

}

void Hook::render(SDL_Renderer* renderer) const {
    b2Vec2 position = body->GetPosition();
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    SDL_Rect rect = {x-25, y, HOOK_X, HOOK_Y};
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);
}