// blocobase.cpp
#include "Bloco.h"
#include "BlocoBase.h"

BlocoBase::BlocoBase(int x, int y, uint8_t r, uint8_t g, uint8_t b) : x(x), y(y), cor({ r, g, b }) {}

void BlocoBase::moverBaixo() {
    y += MOVE_AMOUNT;
}

int BlocoBase::getX() const {
    return x;
}

int BlocoBase::getY() const {
    return y;
}

bool BlocoBase::naParteInferior() const {
    return y >= ALTURA - BLOCO_HEIGHT;
}

void BlocoBase::renderizar(SDL_Renderer* renderer) const {
    SDL_Rect rect = { x, y, BLOCO_WIDTH, BLOCO_HEIGHT };
    SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
}

void BlocoBase::definirPosicao(int x, int y) {
    this->x = x;
    this->y = y;
}

