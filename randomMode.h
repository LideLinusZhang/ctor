#ifndef CTOR_RANDOMMODE_H
#define CTOR_RANDOMMODE_H

#include "boardFactory.h"

class RandomMode : public BoardFactory
{
public:
    RandomMode();

    std::shared_ptr<Board> createBoard(View* view) override;
};

#endif //CTOR_RANDOMMODE_H
