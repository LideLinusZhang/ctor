#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include <random>
#include <algorithm>
#include "boardLayoutFactory.h"

class View;

class RandomMode : public BoardLayoutFactory
{
public:
    RandomMode() = default;
    int createLayout(Board *board) override;
private:
    static std::vector<ResourceType> shuffleResource();
    static std::vector<int> shuffleValues(std::vector<ResourceType> resources);
};

#endif //CTOR_RANDOMMODE_H
