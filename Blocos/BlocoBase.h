// bloconase.h
#ifndef BLOCOBASE_H
#define BLOCOBASE_H

#include <SDL2/SDL.h>
#include "../Constants.h"


class BlocoBase {
public:
    BlocoBase(int x, int y, uint8_t r, uint8_t g, uint8_t b);

    void moverBaixo();
    
    int getX() const;
    int getY() const;
    bool naParteInferior() const;
    void renderizar(SDL_Renderer* renderer) const;
    void definirPosicao(int x, int y);

private:
    int x;
    int y;
    struct Cor {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } cor;
};

#endif
