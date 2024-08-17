#include <SDL2/SDL.h>

struct Sprite {
    SDL_Rect srcRect;
    int frameTime; // Tempo em milissegundos
};