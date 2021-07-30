#ifndef CTOR_BOARDFACTORY_H
#define CTOR_BOARDFACTORY_H

#include <memory>

class Board;
class View;

class BoardFactory
{
public:
    virtual std::shared_ptr<Board> createBoard(View* view) = 0;
};

#endif //CTOR_BOARDFACTORY_H
