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
public:
    static std::vector<std::shared_ptr<Vertex>> createVertices(View* view);
    static std::vector<std::shared_ptr<Edge>> createEdges(View* view, std::vector<std::shared_ptr<Vertex>>* vertices);
    static std::vector<std::vector<int>> createTileVertices();
    int getParkIndex(View *view, std::vector<std::shared_ptr<Tile>> tiles);
    virtual std::shared_ptr<Board> createBoard(View* view) = 0;
};

#endif //CTOR_BOARDLAYOUTFACTORY_H
