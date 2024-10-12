#ifndef ILOGGER_H
#define ILOGGER_H

#include <string>

class ILogger {
public:
    virtual void Log(const std::string& message) = 0;
    virtual ~ILogger() = default;
};

#endif
