#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include <random>
#include <algorithm>
#include "boardFactory.h"

class View;

class RandomMode : public BoardFactory
{
    const int seed;
public:
    explicit RandomMode(const int seed);
    std::shared_ptr<Board> createBoard(View* view) override;
private:
    std::vector<ResourceType> shuffleResource();
    std::vector<int> shuffleValues(std::vector<ResourceType> resources);
};

#endif //CTOR_RANDOMMODE_H
