#ifndef HEART_H
#define HEART_H

#include "../../render/sprites/Sprites.h"
#include <iostream>

class Heart {
public:
  Heart(PortRender *renderer, const std::string &textureId,
        const std::string &texturePath, int totalFrames)
      : isLost(false), removeAfterAnimation(false), renderer(renderer),
        heartSprite(nullptr) {
    std::cout << "Inicializando Heart" << std::endl;
    heartSprite = new Sprites(textureId, texturePath, renderer, 127, 125,
                              totalFrames, 0.1f);
    std::cout << "heartSprite = " << heartSprite << std::endl;
  }

  ~Heart() { delete heartSprite; }

  void update(float deltaTime) {
    if (heartSprite && isLost) {
      heartSprite->update(deltaTime);  // Atualiza a animação do coração
      std::cout << "Atualizando animação do coração perdido." << std::endl;

      if (heartSprite->isLastFrame()) {
        std::cout << "Animação completa para o coração: " << heartSprite << std::endl;
        removeAfterAnimation = true; // Marca para remoção após a animação
      }
    }
  }

  void render(int x, int y) {
    if (heartSprite) {
      if (isLost) {
        heartSprite->render(renderer->getRenderer(), x, y, 127, 125);
      } else {
        heartSprite->renderFullImage(renderer->getRenderer(), x, y, 127, 125);
      }
    }
  }

  void loseHeart() {
    if (!isLost) {
      std::cout << "Heart marcado como perdido. isLost = " << isLost << std::endl;
      isLost = true;                // Marca o coração como perdido
      heartSprite->reset();         // Reinicia a animação do coração
      removeAfterAnimation = false; // Reinicia o estado da remoção
      std::cout << "Animação do coração perdida iniciada." << std::endl;
    }
  }

  bool isAnimationComplete() const { return removeAfterAnimation; }

  // Verifica se o coração está perdido
  bool isLostHeart() const { return isLost; }

private:
  bool isLost;
  bool removeAfterAnimation;
  PortRender *renderer;
  Sprites *heartSprite;
};

#endif // HEART_H
