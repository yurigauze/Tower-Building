#ifndef CONSOLELOGGER_H
#define CONSOLELOGGER_H

#include "ILogger.h"
#include <iostream>

class ConsoleLogger : public ILogger {
public:
    void Log(const std::string& message) override {
        std::cout << message << std::endl;
    }
};

#endif // CONSOLELOGGER_H
