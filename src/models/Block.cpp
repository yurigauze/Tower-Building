#include "Block.h"
#include <box2d/box2d.h>
#include "../render/SDLRenderer.h"
#include <iostream>
#include "rules/ContactListener.h"

Block::Block(b2World *world, PortRender *renderer, b2Vec2 anchorPosition, ILogger *logger)
    : AbstractObject(world, renderer, logger), isReleased(false), isPositioned(false)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pixelsToMeters(B_XPOSITION),
                         pixelsToMeters(B_YPOSITION));
    bodyDef.angle = 0;
    bodyDef.angularDamping = 0.1f;

    body = world_->CreateBody(&bodyDef);
    body->GetUserData().pointer = reinterpret_cast<uintptr_t>(this);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(BLOCK_WIDTH) / 2.0f,
                   pixelsToMeters(BLOCK_HEIGHT) / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 100.0f;
    fixtureDef.friction = 100.0f;
    fixtureDef.restitution = 0.0f;

    body->CreateFixture(&fixtureDef);

    b2BodyDef anchorBodyDef;
    anchorBodyDef.type = b2_staticBody;
    anchorBodyDef.position.Set(pixelsToMeters(anchorPosition.x),
                               pixelsToMeters(anchorPosition.y));
    b2Body *anchorBody = world_->CreateBody(&anchorBodyDef);

    b2RevoluteJointDef jointDef;
    jointDef.bodyA = anchorBody; // Corpo fixo do mundo, o âncora
    jointDef.bodyB = body;       // Corpo dinâmico
    jointDef.localAnchorA.SetZero();
    jointDef.localAnchorB.Set(0, pixelsToMeters(200));
    jointDef.collideConnected = false;

    // ajuste de angulo de balanço
    jointDef.lowerAngle = b2_pi / 2.0f;        // 90º em radianos
    jointDef.upperAngle = 3.0f * b2_pi / 2.0f; // 270º
    jointDef.enableLimit = true;

    joint = world_->CreateJoint(&jointDef);

    color = {0, 255, 0};

    sprites = new Sprites("block", "assets/block.png", renderer);

    if (sprites == nullptr)
    {
        if (logger_)
        {
            logger_->Log("Erro: sprites não foi inicializado corretamente");
        }
    }
}

void Block::release()
{
    if (joint)
    {
        body->SetTransform(body->GetPosition(), 0.0f);
        body->GetWorld()->DestroyJoint(joint);
        joint = nullptr;

        b2Vec2 velocity = body->GetLinearVelocity();
        body->SetLinearVelocity(b2Vec2(0, velocity.y));
        body->SetAngularVelocity(0.0f);
        body->SetAwake(true);

        isReleased = true;
        if (logger_)
        {
            logger_->Log("Bloco liberado: " + std::to_string(reinterpret_cast<uintptr_t>(this)));
        }
    }
}

bool Block::isInContactWithAnotherBlock(ContactListener *contactListener)
{
    bool inContact = contactListener->blocksInContact.count(this) > 0;
    if (logger_)
    {
        logger_->Log("Bloco em contato: " + std::to_string(inContact));
    }
    return inContact;
}

void Block::applyTorque(float torque) { body->ApplyTorque(torque, true); }

void Block::render(PortRender *renderer) const
{
    b2Vec2 position = body->GetPosition();
    float angleRad = body->GetAngle();
    float angleDeg = radiosToGraus(angleRad);

    if (!isReleased)
    {
        angleDeg += 180.0f;
    }

    int renderX = static_cast<int>(metersToPixels(position.x) - BLOCK_WIDTH / 2);
    int renderY = static_cast<int>(metersToPixels(position.y) - BLOCK_HEIGHT / 2);

    SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
    if (sdlRenderer)
    {
        sprites->renderWithRotation(sdlRenderer->getRenderer(), renderX, renderY, BLOCK_WIDTH, BLOCK_HEIGHT, angleDeg);
    }
    else
    {
        if (logger_)
        {
            logger_->Log("Erro: sprites não foi inicializado corretamente");
        }
    }
}