#include "Line.h"
#include <iostream>

    Line::Line(b2World* world_){

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(pixelsToMeters(LINE_XPOSITION),pixelsToMeters(LINE_YPOSITION));
        bodyDef.angle = 0;

        body = world_->CreateBody(&bodyDef);

        b2Vec2 velocity(1.0f / SCALE, 0.0f);
        body->SetLinearVelocity(velocity);
        b2PolygonShape shape;
        shape.SetAsBox(pixelsToMeters(LINE_WIDHT)/2.0f, pixelsToMeters(LINE_HEIGHT)/2.0f);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0.2f;

        body->CreateFixture(&fixtureDef);

        color = {255, 0, 0};

    }
        
    void Line::render(Renderer* renderer) const {
        b2Vec2 position = body->GetPosition();
        int x = static_cast<int>(metersToPixels(position.x) - LINE_WIDHT/2);
        int y = static_cast<int>(metersToPixels(position.y) - LINE_HEIGHT/2);

        renderer->setDrawColor(color.r, color.g, color.b, color.a);
        renderer->drawRect(x, y, LINE_WIDHT, LINE_HEIGHT);
    }