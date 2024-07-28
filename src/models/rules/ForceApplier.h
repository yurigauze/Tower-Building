// ForceApplier.h
#ifndef FORCEAPPLIER_H
#define FORCEAPPLIER_H

#include "../Block.h"
#include <cmath>

class ForceApplier {
public:
    ForceApplier(float amplitude, float frequency, float phase)
        : amplitude(amplitude), frequency(frequency), phase(phase) {}

    void applyForce(Block &block, float time) {
        float torque = amplitude * std::sin(frequency * time + phase);
        block.applyTorque(torque);
    }

private:
    float amplitude;
    float frequency;
    float phase;
};

#endif // FORCEAPPLIER_H
