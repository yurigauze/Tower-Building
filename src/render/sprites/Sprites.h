#ifndef SPRITES_H
#define SPRITES_H

#include <SDL2/SDL.h>
#include <string>
#include "../PortRender.h"

class Sprites {
private:
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    std::string id;
    int frameWidth, frameHeight;
    int currentFrame, totalFrames;
    float frameTime, currentFrameTime;
    PortRender* renderer;

public:
    Sprites(const std::string& id, const std::string& filePath, PortRender* renderer, int frameWidth = -1, int frameHeight = -1, int totalFrames = 1, float frameTime = 0.0f);
    ~Sprites();
    void update(float deltaTime);
    void render(SDL_Renderer* renderer, int x, int y, int width, int height);
    void renderFullImage(SDL_Renderer* renderer, int x, int y, int width, int height);
    void renderWithRotation(SDL_Renderer* renderer, int x, int y, int width, int height, double angle);

    int getFrameWidth() const { return frameWidth; }
    int getFrameHeight() const { return frameHeight; }
    std::string getID() const { return id; }
};

#endif // SPRITES_H
