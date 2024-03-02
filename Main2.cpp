#include <SDL2/SDL.h>
#include <vector>
#include <random>

const int LARGURA = 600;
const int ALTURA = 850;
const int BLOCO_WIDTH = 188;
const int BLOCO_HEIGHT = 134;
const int MOVE_AMOUNT = 15; // Quantidade de pixels que o bloco se move a cada quadro

class Bloco {
public:
    Bloco(int x, int y, uint8_t r, uint8_t g, uint8_t b) : x(x), y(y), cor({ r, g, b }) {}

    void moverBaixo() {
        y += MOVE_AMOUNT;
    }
    
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    bool naParteInferior() const {
        return y >= ALTURA - BLOCO_HEIGHT;
    }

    void renderizar(SDL_Renderer* renderer) const {
        SDL_Rect rect = { x, y, BLOCO_WIDTH, BLOCO_HEIGHT };
        SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    void definirPosicao(int x, int y) {
        this->x = x;
        this->y = y;
    }

private:
    int x;
    int y;
    struct Cor {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } cor;
};

class BlocoBase {
public:
    BlocoBase(int x, int y, uint8_t r, uint8_t g, uint8_t b) : x(x), y(y), cor({ r, g, b }) {}


    bool naParteInferior() const {
        return y >= ALTURA - BLOCO_HEIGHT;
    }
    
    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    void renderizar(SDL_Renderer* renderer) const {
        SDL_Rect rect = { x, y, BLOCO_WIDTH, BLOCO_HEIGHT };
        SDL_SetRenderDrawColor(renderer, cor.r, cor.g, cor.b, SDL_ALPHA_OPAQUE);
        SDL_RenderFillRect(renderer, &rect);
    }

    void definirPosicao(int x, int y) {
        this->x = x;
        this->y = y;
    }

private:
    int x;
    int y;
    struct Cor {
        uint8_t r;
        uint8_t g;
        uint8_t b;
    } cor;
};


int random_num() {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, 255);
    return dis(gen);
}

bool colisaoBase(const Bloco& bloco, const BlocoBase& blocoBase) {

    if (bloco.getX() + BLOCO_WIDTH <= blocoBase.getX() || blocoBase.getX() + BLOCO_WIDTH <= bloco.getX()) {
        return false;
    }
   
    if (bloco.getY() + BLOCO_HEIGHT <= blocoBase.getY() || blocoBase.getY() + BLOCO_HEIGHT <= bloco.getY()) {
        return false;
    }

    return true;
}

bool colisao(const Bloco& bloco1, const Bloco& bloco2) {
    if (bloco1.getX() + BLOCO_WIDTH <= bloco2.getX() || bloco2.getX() + BLOCO_WIDTH <= bloco1.getX()) {
        return false;
    }
   
    if (bloco1.getY() + BLOCO_HEIGHT <= bloco2.getY() || bloco2.getY() + BLOCO_HEIGHT <= bloco1.getY()) {
        return false;
    }

    return true;
}



int main(int argc, char* argv[]) {
    SDL_Window* janela = NULL;
    SDL_Renderer* renderer = NULL;

    SDL_Init(SDL_INIT_VIDEO);
    janela = SDL_CreateWindow("Tower Building", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        LARGURA, ALTURA, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(janela, -1, SDL_RENDERER_ACCELERATED);

    BlocoBase blocoBase(LARGURA / 2 - BLOCO_WIDTH / 2, 666, 0, 255, 0);
    std::vector<Bloco> blocos;
    blocos.emplace_back(LARGURA / 2 - BLOCO_WIDTH / 2, 100, 255, 0, 0); 

    bool continua = true;
    SDL_Event evento;

while (continua) {
    while (SDL_PollEvent(&evento)) {
        if (evento.type == SDL_QUIT) {
            continua = false;
        } else if (evento.type == SDL_KEYDOWN) {
            if (evento.key.keysym.sym == SDLK_SPACE) {
                // Move o bloco para baixo até atingir a parte inferior da tela
                while (!blocos[0].naParteInferior()) {
                    blocos[0].moverBaixo();
                    SDL_SetRenderDrawColor(renderer, 133, 193, 233, SDL_ALPHA_OPAQUE);
                    SDL_RenderClear(renderer);
                    for (const auto& bloco : blocos) {
                        bloco.renderizar(renderer);
                        blocoBase.renderizar(renderer);
                    }
                    SDL_RenderPresent(renderer);
                    SDL_Delay(5);
                    
                    // Verifica colisão entre o primeiro bloco e o bloco base
                    if (colisaoBase(blocos[0], blocoBase)) {
                        // Define a posição do bloco para que ele fique em cima do bloco base
                        blocos[0].definirPosicao(blocos[0].getX(), blocoBase.getY() - BLOCO_HEIGHT);
                        break; 
                    }
                    
                    // Verifica colisão entre o bloco que está descendo e os blocos já empilhados
                    bool colidiu = false;
                    for (auto it = std::next(blocos.begin()); it != blocos.end(); ++it) {
                        if (colisao(blocos[0], *it)) {
                            blocos[0].definirPosicao(blocos[0].getX(), it->getY() - BLOCO_HEIGHT);
                            colidiu = true;
                            break;
                        }
                    }
                    if (colidiu) {
                        break;
                    }
                }
                
                // Adiciona o bloco atual à pilha de blocos
                blocos.push_back(blocos[0]);
                // Adiciona um novo bloco na parte de cima
                // Utilizei random_num para gerar com cores diferentes
                blocos[0] = Bloco(LARGURA / 2 - BLOCO_WIDTH / 2, 100, random_num(), random_num(), random_num());
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 133, 193, 233, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);

    // Renderiza todos os blocos
    for (const auto& bloco : blocos) {
        bloco.renderizar(renderer);
    }
    blocoBase.renderizar(renderer);

    SDL_RenderPresent(renderer);
    SDL_Delay(10);
}

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(janela);
    SDL_Quit();
    return 0;
}

