#include "Utils.h"
#include <cmath>
#include <random>

static std::mt19937 gen;

int random_num() {
  std::uniform_int_distribution<int> dis(0, 255);
  return dis(gen);
}

float metersToPixels(float meters) { return meters * SCALE; }

float radiosToGraus(float radian) { return radian * (180.f / M_PI); }

float grausToRadios(float graus) { return graus * (M_PI / 180.f); }

float pixelsToMeters(float pixels) { return pixels / SCALE; }

void random_initialize() {
  std::random_device rd;
  gen.seed(rd());
}
