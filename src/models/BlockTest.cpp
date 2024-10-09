#include "BlockTest.h"
#include "../render/SDLRenderer.h"
#include <iostream>

BlockTest::BlockTest(b2World *world, PortRender *renderer, b2Vec2 position)
    : AbstractObject(world, renderer)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(pixelsToMeters(position.x), pixelsToMeters(position.y));
    bodyDef.fixedRotation = true;

    body = world_->CreateBody(&bodyDef);
    body->SetGravityScale(0.0f);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(BLOCK_WIDTH) / 2.0f, pixelsToMeters(BLOCK_HEIGHT) / 2.0f);

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 1.0f; 
    fixtureDef.friction = 0.3f; 
    fixtureDef.restitution = 0.1f;

    body->CreateFixture(&fixtureDef);

    color = {0, 0, 255}; 
    sprites = new Sprites("block_test", "assets/block.png", renderer);

    if (sprites == nullptr) {
        std::cerr << "Erro: sprites não foi inicializado corretamente" << std::endl;
    }
}

void BlockTest::render(PortRender *renderer) const
{
    b2Vec2 position = body->GetPosition();
    int renderX = static_cast<int>(metersToPixels(position.x) - BLOCK_WIDTH / 2);
    int renderY = static_cast<int>(metersToPixels(position.y) - BLOCK_HEIGHT / 2);

    // std::cerr << "BLOCO TESTE Posição X: "<< position.x << std::endl;


    SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
    if (sdlRenderer) {
        sprites->renderFullImage(sdlRenderer->getRenderer(), renderX, renderY, BLOCK_WIDTH, BLOCK_HEIGHT);
    } else {
        std::cerr << "Renderer is not an SDLRenderer" << std::endl;
    }
}
