#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include "boardFactory.h"

class RandomMode : public BoardFactory
{
    const int seed;
public:
    explicit RandomMode(const int seed);

    std::shared_ptr<Board> createBoard(View* view) override;
};

#endif //CTOR_RANDOMMODE_H
