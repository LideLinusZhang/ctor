#ifndef CTOR_BOARDLAYOUTFACTORY_H
#define CTOR_BOARDLAYOUTFACTORY_H

#include <vector>
#include <memory>
#include "../models/board.h"
#include "../types/resourceType.h"
#include "../models/tile.h"
#include "../models/vertex.h"
#include "../models/edge.h"

#define TOTAL_TILES 19

class View;

class BoardLayoutFactory
{
protected:
    const int tileVertices[19][6] {
        {0,1,3,4,8,9},
        {2,3,7,8,13,14},
        {4,5,9,10,15,16},
        {6,7,12,13,18,19},
        {8,9,14,15,20,21},
        {10,11,16,17,22,23},
        {13,14,19,20,25,26},
        {15,16,21,22,27,28},
        {18,19,24,25,30,31},
        {20,21,26,27,32,33},
        {22,23,28,29,34,35},
        {25,26,31,32,37,38},
        {27,28,33,34,39,40},
        {30,31,36,37,42,43},
        {32,33,38,39,44,45},
        {34,35,40,41,46,47},
        {37,38,43,44,49,50},
        {39,40,45,46,51,52},
        {44,45,49,50,52,53}
    };
public:
    virtual std::vector<std::shared_ptr<Tile>> createLayout(View* view) = 0;
};

#endif //CTOR_BOARDLAYOUTFACTORY_H
