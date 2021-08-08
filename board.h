#ifndef CTOR_BOARD_H
#define CTOR_BOARD_H

#include <vector>
#include <memory>

class View;

class Tile;

class BoardLayoutFactory;

class Vertex;

class Geese;

class Edge;

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
    View *view;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::shared_ptr<Vertex>> vertices;
    std::shared_ptr<Geese> geese;
public:
    explicit Board(View *view);

    Tile *getTile(int index) const;
    Edge *getEdge(int index) const;
    Vertex *getVertex(int index) const;
    Geese *getGeese() const;

    void reset(); //Set all board elements to their initial state (the state at the beginning of a game).

    void print() const;
    std::string toString() const;
private:
    friend class BoardLayoutFactory;
};

#endif //CTOR_BOARD_H
