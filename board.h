#ifndef CTOR_BOARD_H
#define CTOR_BOARD_H

#include <vector>
#include <memory>
#include "geese.h"

class View;
class Tile;
class Edge;
class Vertex;

class Board
{
    View* view;
    std::vector<std::shared_ptr<Tile>> tiles;
    std::vector<std::shared_ptr<Edge>> edges;
    std::vector<std::shared_ptr<Vertex>> vertices;
    Geese geese;
public:
    // Construct by copying pre-constructed vectors.
    Board(View* view, std::vector<std::shared_ptr<Tile>> tiles, std::vector<std::shared_ptr<Edge>> edges,
          std::vector<std::shared_ptr<Vertex>> vertices, int geeseInitialPosition);

    Tile* getTile(int index) const;
    Edge* getEdge(int index) const;
    Vertex* getVertex(int index) const;

    void moveGeese(int tileIndex);

    void print() const;
};

#endif //CTOR_BOARD_H
