#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include <random>
#include "boardFactory.h"

class View;

// use the static Random class for random number generation.

class RandomMode : public BoardFactory
{
public:
    RandomMode();
    std::shared_ptr<Board> createBoard(View* view) override;

private: 
    std::map<ResourceType, int> resources = {{ResourceType::Wifi, 3}, 
                                                {ResourceType::Heat, 3},
                                                {ResourceType::Brick, 4},
                                                {ResourceType::Energy, 4},
                                                {ResourceType::Glass, 4},
                                                {ResourceType::Parl, 1},
                                                }
};

#endif //CTOR_RANDOMMODE_H
