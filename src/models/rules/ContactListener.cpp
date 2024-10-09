#include "ContactListener.h"
#include "../Block.h"
#include <iostream>

void ContactListener::BeginContact(b2Contact* contact) {
    Block* blockA = reinterpret_cast<Block*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
    Block* blockB = reinterpret_cast<Block*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

    if (blockA) {
        blocksInContact.insert(blockA);
        std::cout << "Bloco A em contato: " << blockA << std::endl;
    }
    if (blockB) {
        blocksInContact.insert(blockB);
        std::cout << "Bloco B em contato: " << blockB << std::endl;
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

