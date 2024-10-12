#include "ContactListener.h"
#include "../Block.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact) {
    Block* blockA = reinterpret_cast<Block*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    Block* blockB = reinterpret_cast<Block*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (blockA) {
        blocksInContact.insert(blockA);
        logger->Log("Bloco A em contato: " + std::to_string(reinterpret_cast<uintptr_t>(blockA)));
    }
    if (blockB) {
        blocksInContact.insert(blockB);
        logger->Log("Bloco B em contato: " + std::to_string(reinterpret_cast<uintptr_t>(blockB)));
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
