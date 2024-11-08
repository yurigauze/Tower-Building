#include "BaseBlock.h"
#include "../render/SDLRenderer.h"
#include <iostream>

BaseBlock::BaseBlock(b2World *world, PortRender *renderer)
    : AbstractObject(world, renderer)
{

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody; // Tipo de corpo dinâmico
    bodyDef.position.Set(pixelsToMeters(BB_XPOSITION),
                         pixelsToMeters(BB_YPOSITION)); // Posição do corpo
    body = world_->CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(pixelsToMeters(200) / 2.0f,
                   pixelsToMeters(BLOCK_HEIGHT) / 2.0f);


    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = 10.0f;
    fixtureDef.friction = 10.0f;
    fixtureDef.restitution = 0.0f;

    body->CreateFixture(&fixtureDef);

    color = {0, 255, 0};

    sprites =
        new Sprites("bblock", "assets/block.png", renderer);
}

void BaseBlock::render(PortRender *renderer, Camera &camera) const
{
    b2Vec2 position = body->GetPosition();

    int renderX = static_cast<int>(metersToPixels(position.x) - BLOCK_WIDTH / 2);
    int renderY = static_cast<int>(metersToPixels(position.y) - BLOCK_HEIGHT / 2);

    renderY -= camera.getView().y;

    SDLRenderer *sdlRenderer = dynamic_cast<SDLRenderer *>(renderer);
    if (sdlRenderer)
    {
        sprites->renderFullImage(sdlRenderer->getRenderer(), renderX, renderY, BLOCK_WIDTH, BLOCK_HEIGHT);
    }
    else
    {
        std::cerr << "Renderer is not an SDLRenderer" << std::endl;
    }
}
