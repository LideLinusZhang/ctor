#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include <random>
#include <algorithm>
#include "boardLayoutFactory.h"

class View;

class RandomMode : public BoardLayoutFactory
{
public:
    RandomMode();
    std::shared_ptr<Board> createBoard(View* view) override;
private:
    std::vector<ResourceType> shuffleResource();
    std::vector<int> shuffleValues(std::vector<ResourceType> resources);
};

#endif //CTOR_RANDOMMODE_H
