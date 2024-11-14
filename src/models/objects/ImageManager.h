#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <vector>

class ImageManager {
public:
    ImageManager(PortRender *renderer, Camera *camera)
        : renderer_(renderer), camera_(camera) 
    {
        // Aqui instanciamos todas as classes que vão ser gerenciadas
        // clouds_ = new Clouds(renderer, "clouds", "assets/clouds.png");

    }

    ~ImageManager() {
       // delete clouds_;
       // delete background_;
    }

    void renderImages(int screenWidth, int screenHeight) {
      //  background_->render(screenWidth, screenHeight);
      //  clouds_->render(100, 50); 
    }

private:
    // PortRender *renderer_;
    // Camera *camera_;
    // Clouds *clouds_;
    // Background *background_;
};

#endif // IMAGEMANAGER_H
