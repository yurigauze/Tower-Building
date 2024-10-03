#include "ContactListener.h"
#include "../Block.h"

void ContactListener::BeginContact(b2Contact* contact) {
    Block* blockA = reinterpret_cast<Block*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    Block* blockB = reinterpret_cast<Block*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (blockA) {
        blocksInContact.insert(blockA);
    }
    if (blockB) {
        blocksInContact.insert(blockB);
    }
}

void ContactListener::EndContact(b2Contact* contact) {
    Block* blockA = reinterpret_cast<Block*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    Block* blockB = reinterpret_cast<Block*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (blockA) {
        blocksInContact.erase(blockA);
    }
    if (blockB) {
        blocksInContact.erase(blockB);
    }
}

