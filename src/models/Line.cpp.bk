#include "Line.h"
#include <iostream>

Line::Line(b2World* world_){

    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pixelsToMeters(LINE_XPOSITION),pixelsToMeters(LINE_YPOSITION));
    bodyDef.angle = 0;

    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(LINE_WIDHT)/2.0f, pixelsToMeters(LINE_HEIGHT)/2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 9.0f;
    fixtureDef.friction = 0.5f;
    fixtureDef.restitution = 0.2f;

    body->CreateFixture(&fixtureDef);

    color = {255, 0, 255};

    //Criação da junta
    b2BodyDef anchorDef;
    anchorDef.position.Set(pixelsToMeters(LINE_XPOSITION), pixelsToMeters(LINE_YPOSITION) - pixelsToMeters(LINE_HEIGHT));
    b2Body* anchorBody = world_->CreateBody(&anchorDef);

    b2DistanceJointDef jointDef;
    jointDef.Initialize(anchorBody, body, anchorBody->GetWorldCenter(), body->GetWorldCenter());
    jointDef.collideConnected = true;  // Permite que os corpos conectados colidam entre si

    world_->CreateJoint(&jointDef);

}

b2Body* Line::getBody() const {
    return body;
}
        
void Line::render(PortRender* renderer) const {

    b2Vec2 position = body->GetPosition();

    int x = static_cast<int>(metersToPixels(position.x) - (LINE_WIDHT / 2));
    int y = static_cast<int>(metersToPixels(position.y) - (LINE_HEIGHT / 2));

    renderer->setDrawColor(color.r, color.g, color.b, color.a);
    renderer->drawRect(x, y, LINE_WIDHT, LINE_HEIGHT);
}
