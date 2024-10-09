// ContactListener.h

#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include "../../include/box2d/box2d.h"
#include <set>

class Block;

class ContactListener : public b2ContactListener {
public:
    std::set<Block*> blocksInContact; 

    void BeginContact(b2Contact* contact) override;
    void EndContact(b2Contact* contact) override;
};

#endif
