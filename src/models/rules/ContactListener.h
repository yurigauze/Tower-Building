#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "../../include/box2d/box2d.h"
#include <set>

class Block;
class ILogger;

class ContactListener : public b2ContactListener {
public:
    std::set<Block*> blocksInContact; 
    ILogger* logger;

    ContactListener(ILogger* logger) : logger(logger) {}

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};

#endif
