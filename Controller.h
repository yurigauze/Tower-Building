#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <list>
#include "Blocks/Block.h"

class Controller {
public:
    Controller();
    ~Controller();

    void addBlock(Block* block);
    void removeBlock(Block* block);
    const std::list<Block*>& getBlocks() const;

private:
    std::list<Block*> blocks;
};

#endif // CONTROLLER_H