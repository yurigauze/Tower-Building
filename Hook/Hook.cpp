#include "Hook.h"
#include "Line.h"

Hook::Hook(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(HOOK_XPOSITION,HOOK_YPOSITION);
    bodyDef.angle = 0;

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    float boxWidth = std::max(static_cast<float>(HOOK_WIDTH) / 2, 0.1f);
    float boxHeight = std::max(static_cast<float>(HOOK_HEIGHT) / 2, 0.1f);
    shape.SetAsBox(boxWidth, boxHeight);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.2f;

    body->CreateFixture(&fixtureDef);

    color = {0, 255, 0};

    // Criação da linha para centralizar no gancho
    float lineX = HOOK_XPOSITION;
    float lineY = HOOK_YPOSITION;
    line = new Line(world_, lineX, lineY);

    //Conectar a linha ao gancho
    b2RevoluteJointDef jointDef;
    jointDef.bodyA = line->getBody();  // Corpo da ponta superior da linha
    jointDef.bodyB = body;             // Corpo do gancho
    jointDef.localAnchorA.Set(0,-LINE_HEIGHT/2); // Ancora na ponta superior da linha
    jointDef.localAnchorB.Set(0, 0);  // Ancora na parte inferior do gancho
    jointDef.enableMotor = false;

    jointWithLine = static_cast<b2RevoluteJoint*>(world_->CreateJoint(&jointDef));

}

void Hook::render(Renderer* renderer) const {
    line->render(renderer);

    b2Vec2 position = body->GetPosition();
    int x = static_cast<int>(position.x - HOOK_WIDTH/2);
    int y = static_cast<int>(position.y - HOOK_HEIGHT/2);

    renderer->setDrawColor(color.r, color.g, color.b, color.a);
    renderer->drawRect(x, y, HOOK_WIDTH, HOOK_HEIGHT);
}

void Hook::setJointWithLine(b2RevoluteJoint* joint) {
    jointWithLine = joint;
}

void Hook::setMotorSpeed(float speed) {
    if (jointWithLine) {
        jointWithLine->SetMotorSpeed(speed);
    }
}