    #include "Line.h"

    Line::Line(b2World* world_, float x, float y, float width, float height){

        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(x,y);
        bodyDef.angle = 0;

        body = world_->CreateBody(&bodyDef);

        b2PolygonShape shape;
        shape.SetAsBox(width/2, height/2);

        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 1.0f;
        fixtureDef.friction = 0.5f;
        fixtureDef.restitution = 0.2f;

        body->CreateFixture(&fixtureDef);

        color = {0, 200, 200};

        //corpo que prenderá o gancho  
        b2BodyDef hookBodyDef;
        hookBodyDef.type = b2_dynamicBody;
        hookBodyDef.position.Set(x, y + height);  // Posição abaixo da linha
        hookBodyDef.angle = 0;

        b2Body* hookBody = world_->CreateBody(&hookBodyDef);

        b2RevoluteJointDef jointDef;
        jointDef.bodyA = body;
        jointDef.bodyB = hookBody;
        jointDef.localAnchorA.Set(0, height / 2);  // Ancora na parte superior da linha
        jointDef.localAnchorB.Set(0, 0);           // Ancora no centro do gancho
        jointDef.enableMotor = true;

        jointWithHook = static_cast<b2RevoluteJoint*>(world_->CreateJoint(&jointDef));

    }
    
    void Line::render(Renderer* renderer) const {
        b2Vec2 position = body->GetPosition();
        int x = static_cast<int>(position.x);
        int y = static_cast<int>(position.y);

        renderer->setDrawColor(color.r, color.g, color.b, color.a);
        renderer->drawRect(x, y, HOOK_X, HOOK_Y);
    }

    void Line::attachToHook(b2Body* hookBody) {
}

    void Line::setMotorSpeed(float speed) {
    if (jointWithHook) {
        jointWithHook->SetMotorSpeed(speed);
    }
}