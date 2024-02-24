#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include "constant.h"
#include "engine.h"

class Utils{
public:
    static bool checkMoveDown(Engine& engine);
    static double getMoveDownValue(Engine& engine, bool store);
};

#endif // UTILS_H