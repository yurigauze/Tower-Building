// TextureManager.h
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include "../PortRender.h"
#include "../SDLRenderer.h"
#include <SDL2/SDL.h>
#include <map>
#include <string>

class TextureManager {
public:
    TextureManager(PortRender *renderer);
    ~TextureManager();

    bool loadTexture(const std::string &id, const std::string &filename);
    void drawTexture(const std::string &id, float x, float y, SDL_Rect *srcRect = nullptr);

private:
    PortRender *renderer;
    std::map<std::string, SDL_Texture*> textures;
};

#endif // TEXTUREMANAGER_H
