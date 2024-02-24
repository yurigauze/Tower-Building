#include <utils.h>

bool Utils::checkMoveDown(Engine& engine){
    return engine.checkTimeMovement(Engine::MOVE_DOWN_MOVEMENT);
}

double Utils::getMoveDownValue(Engine& engine, bool store){
    double pixelsPerFrame;
    if (store){
        // Implementação específica se store for verdadeiro
    }
    else{
        pixelsPerFrame = engine.pixelsPerFrame();
    }

    int successCount = engine.getVariable(Constant::SUCCESS_COUNT);
    int calHeight = engine.getVariable(Constant::BLOCK_HEIGHT) * 2;

    if (successCount <= 4){
        return pixelsPerFrame * (calHeight * 1.25);
    }
    else{
        return pixelsPerFrame * calHeight;
    }
}
