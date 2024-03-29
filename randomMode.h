#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include "boardLayoutFactory.h"
#include "resourceType.h"

class View;

const int tileNumberByResource[totalResourceTypes] {4, 4, 4, 3, 3}; // Ordered as in ResourceType

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
