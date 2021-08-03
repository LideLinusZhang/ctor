#ifndef CTOR_BOARD_H
#define CTOR_BOARD_H

#include <vector>
#include <memory>
#include "vertex.h"
#include "edge.h"
#include "geese.h"

class View;
class Tile;
class BoardLayoutFactory;

const int totalTiles = 19;
const int minTileIndex = 0;
const int maxTileIndex = 18;

const int totalEdges = 72;
const int minEdgeIndex = 0;
const int maxEdgeIndex = 71;

const int totalVertices = 54;
const int minVertexIndex = 0;
const int maxVertexIndex = 53;

class Board
{
    View* view;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::shared_ptr<Geese> geese;
public:
    explicit Board(View* view);
    
    Tile* getTile(int index) const;
    Edge* getEdge(int index) const;
    Vertex* getVertex(int index) const;

    bool tryMoveGeese(int tileIndex);
    Geese* getGeese() const;

    void print() const;
    std::string toString() const;
private: 
    // Pass this board to its components.
    void setBoard();

    friend class BoardLayoutFactory;
};

#endif //CTOR_BOARD_H
