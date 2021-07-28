#ifndef CTOR_BOARDFACTORY_H
#define CTOR_BOARDFACTORY_H

#include <memory>

class Board;

class BoardFactory
{
public:
    virtual std::shared_ptr<Board> createBoard() = 0;
};

#endif //CTOR_BOARDFACTORY_H
