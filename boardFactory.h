#ifndef CTOR_BOARDFACTORY_H
#define CTOR_BOARDFACTORY_H

#include <vector>
#include <memory>
#include "resourceType.h"

#define TOTAL_TILES 19

class Board;
class View;
class Tile;
class Edge;
class Vertex;

class BoardFactory
{
public:
    static std::vector<std::shared_ptr<Vertex>> createVertices(View* view);
    static std::vector<std::shared_ptr<Edge>> createEdges(View* view, std::vector<std::shared_ptr<Vertex>>* vertices);
    static std::vector<std::vector<int>> createTileVertices();
    int getParkIndex(View *view, std::vector<std::shared_ptr<Tile>> tiles);
    virtual std::shared_ptr<Board> createBoard(View* view) = 0;
};

#endif //CTOR_BOARDFACTORY_H
