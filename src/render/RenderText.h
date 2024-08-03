#ifndef RENDER_TEXT_H
#define RENDER_TEXT_H

#include <string>
#include <SDL2/SDL_ttf.h>

class TextRenderer {
public:
    TextRenderer(SDL_Renderer* renderer, const std::string& fontPath, int fontSize) {
        font_ = TTF_OpenFont(fontPath.c_str(), fontSize);
        if (!font_) {
            throw std::runtime_error("Failed to load font");
        }
        renderer_ = renderer;
    }

    ~TextRenderer() {
        if (font_) {
            TTF_CloseFont(font_);
        }
    }

    void renderText(const std::string& text, int x, int y, const SDL_Color& color) {
        SDL_Surface* surface = TTF_RenderText_Solid(font_, text.c_str(), color);
        if (surface) {
            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer_, surface);
            if (texture) {
                SDL_Rect destRect = {x, y, surface->w, surface->h};
                SDL_RenderCopy(renderer_, texture, NULL, &destRect);
                SDL_DestroyTexture(texture);
            }
            SDL_FreeSurface(surface);
        }
    }

private:
    SDL_Renderer* renderer_;
    TTF_Font* font_;
};

#endif // RENDER_TEXT_H
