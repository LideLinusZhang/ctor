#ifndef CTOR_BOARDLAYOUTFACTORY_H
#define CTOR_BOARDLAYOUTFACTORY_H

#include <vector>
#include <memory>
#include "../models/board.h"
#include "../types/resourceType.h"
#include "../models/tile.h"
#include "../models/vertex.h"
#include "../models/edge.h"

class View;

class BoardLayoutFactory
{
protected:
    // Set the board's layout by moving tiles vector.
    static void setLayout(Board* board, std::vector<std::shared_ptr<Tile>>& tiles);
public:
    // Create layout for board, returning tile index of the park.
    virtual int createLayout(Board* board) = 0;
};

#endif //CTOR_BOARDLAYOUTFACTORY_H
