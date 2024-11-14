// ClickableSprite.h
#ifndef CLICKABLESPRITE_H
#define CLICKABLESPRITE_H

#include "Sprites.h"
#include <iostream>

class ClickableSprite : public Sprites
{
public:
    ClickableSprite(const std::string &id, const std::string &filePath, PortRender *renderer)
        : Sprites(id, filePath, renderer,
                  -1, -1, -1, 0.0f) {}

    bool isClicked(int mouseX, int mouseY) const
    {
        SDL_Rect rect = getRect();
        return mouseX >= rect.x && mouseX <= (rect.x + rect.w) &&
               mouseY >= rect.y && mouseY <= (rect.y + rect.h);
    }

    void onClick()
    {
        std::cout << "Imagem clicada!" << std::endl;
    }
};

#endif // CLICKABLESPRITE_H