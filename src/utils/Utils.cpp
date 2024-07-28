#include "Utils.h"
#include <random>

static std::mt19937 gen;

int random_num() {
    std::uniform_int_distribution<int> dis(0, 255);
    return dis(gen);
}

float metersToPixels(float meters) {
    return meters * SCALE;
}

float pixelsToMeters(float pixels) {
    return pixels / SCALE;
}

void random_initialize(){
    std::random_device rd;
    gen.seed( rd() );
}

