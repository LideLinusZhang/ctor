#ifndef CTOR_BOARDLAYOUTFACTORY_H
#define CTOR_BOARDLAYOUTFACTORY_H

#include <vector>
#include <memory>

class View;

class Board;

class Tile;

class BoardLayoutFactory
{
protected:
    // Set the board's layout by moving tiles vector.
    static void setLayout(Board *board, std::vector<std::unique_ptr<Tile>> &tiles);
public:
    // Create layout for board, returning tile index of the park.
    virtual int createLayout(Board *board) = 0;
};

#endif //CTOR_BOARDLAYOUTFACTORY_H
