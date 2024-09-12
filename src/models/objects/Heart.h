#ifndef HEART_H
#define HEART_H

#include "../../render/sprites/Sprites.h"
#include <iostream>

class Heart {
public:
  Heart(PortRender *renderer, const std::string &textureId,
        const std::string &texturePath, int totalFrames)
      : isLost(false), renderer(renderer), heartSprite(nullptr) {
    // Inicializa o Sprites para o coração
    heartSprite = new Sprites(textureId, texturePath, renderer, 127, 125,
                              totalFrames, 0.1f);
  }

  ~Heart() { delete heartSprite; }

  void update(float deltaTime) {
    if (heartSprite && isLost) {
      heartSprite->update(deltaTime); // Atualiza a animação se estiver perdido
      std::cout << "Atualizando animação do coração perdido." << std::endl;
    }
  }

  void render(int x, int y) {
    if (heartSprite) {
      std::cout << "Estado do coração: " << (isLost ? "Perdido" : "Não perdido")
                << std::endl;

      if (isLost) {
        // Renderiza a animação do coração se estiver perdido
        heartSprite->render(renderer->getRenderer(), x, y, 127, 125);
        std::cout << "Renderizando animação do coração perdido." << std::endl;
      } else {
        heartSprite->renderFullImage(renderer->getRenderer(), x, y, 127, 125);
        std::cout << "Renderizando coração estático." << std::endl;
      }
    }
  }

  void loseHeart() {
    isLost = true;
    std::cout << "Heart marked as lost." << std::endl;
  }

  bool isAnimationComplete() const { return heartSprite->isLastFrame(); }

private:
  bool isLost;
  PortRender *renderer;
  Sprites *heartSprite;
};

#endif // HEART_H
