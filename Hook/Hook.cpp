#include "Hook.h"
#include "Line.h"

Hook::Hook(b2World* world_, float x, float y, float width, float height){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(x,y);
    bodyDef.angle = 0;

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    float boxWidth = std::max(width / 2, 0.1f);
    float boxHeight = std::max(height / 2, 0.1f);
    shape.SetAsBox(boxWidth, boxHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.2f;

    body->CreateFixture(&fixtureDef);

    cor = {0, 255, 0};

    // Ajuste a criação da linha para centralizar no gancho
    float lineX = x;
    float lineY = y;
    line = new Line(world_, lineX, lineY, LINE_X, LINE_Y);

    //conectar a linha ao gancho
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = line->getBody();  // Corpo da ponta superior da linha
    jointDef.bodyB = body;                // Corpo do gancho
    jointDef.localAnchorA.Set(0,-LINE_Y/2);       // Ancora na ponta superior da linha
    jointDef.localAnchorB.Set(0, 0);  // Ancora na parte inferior do gancho
    jointDef.enableMotor = false;

    jointWithLine = static_cast<b2RevoluteJoint*>(world_->CreateJoint(&jointDef));

}

void Hook::render(SDL_Renderer* renderer) const {
    line->render(renderer);

    b2Vec2 position = body->GetPosition();
    int x = static_cast<int>(position.x);
    int y = static_cast<int>(position.y);

    SDL_Rect rect = {x - HOOK_X / 2, y - HOOK_Y / 2, HOOK_X, HOOK_Y};
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawRect(renderer, &rect);
}

void Hook::setJointWithLine(b2RevoluteJoint* joint) {
    jointWithLine = joint;
}

void Hook::setMotorSpeed(float speed) {
    if (jointWithLine) {
        jointWithLine->SetMotorSpeed(speed);
    }
}