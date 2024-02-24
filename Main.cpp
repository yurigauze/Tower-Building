#include <SDL2/SDL.h>

const int LARGURA = 600;
const int ALTURA = 850;

typedef unsigned char uint8;

SDL_Renderer *atributos = NULL;

void setColor(uint8 r, uint8 g, uint8 b)
{
    SDL_SetRenderDrawColor(atributos, r, g, b, SDL_ALPHA_OPAQUE);
}

void setBackColor(uint8 r, uint8 g, uint8 b)
{
    setColor(r, g, b);
    SDL_RenderClear(atributos);
}

void update(SDL_Rect *box)
{
    box->y += 1; // Incremento de 1 na posição Y (velocidade de queda)
}

int main(int argc, char *argv[])
{
    SDL_Window *janela = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    janela = SDL_CreateWindow("Tower Building", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                              LARGURA, ALTURA, SDL_WINDOW_SHOWN);

    atributos = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    setBackColor(133, 193, 233);

    setColor(255, 0, 0);
    SDL_Rect box;
    box.x = (LARGURA / 2) - (188 / 2);
    box.y = 666;
    box.w = 188;
    box.h = 134;

    SDL_Rect box2;
    box2.x = (LARGURA / 2) - (188 / 2);
    box2.y = 200;
    box2.w = 188;
    box2.h = 134;

    SDL_RenderFillRect(atributos, &box);
    SDL_RenderFillRect(atributos, &box2);

    bool continua = true;
    SDL_Event evento;

    Uint32 lastTime = SDL_GetTicks(); // Tempo da última atualização

    while (continua)
    {
        Uint32 currentTime = SDL_GetTicks();       // Tempo atual
        Uint32 deltaTime = currentTime - lastTime; // Tempo decorrido desde a última atualização

        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                continua = false;
                break;
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    continua = false;
                    break;
                case SDLK_LEFT:
                    box2.x -= 15;
                    break;
                case SDLK_RIGHT:
                    box2.x += 15;
                    break;
                case SDLK_UP:
                    box2.y -= 15;
                    break;
                case SDLK_DOWN:
                    // Atualizar a posição do retângulo a cada quadro
                    while (box2.y + box2.h < ALTURA && deltaTime >= 10)
                    { // Controla a velocidade de queda
                        update(&box2);
                        deltaTime -= 10;
                    }
                    break;
                }
                break;
            }
        }

        setBackColor(133, 193, 233);
        setColor(255, 0, 0);
        SDL_RenderFillRect(atributos, &box);
        SDL_RenderFillRect(atributos, &box2);
        SDL_RenderPresent(atributos);

        lastTime = currentTime; // Atualiza o tempo da última atualização
    }

    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}
