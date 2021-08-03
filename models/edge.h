#ifndef CTOR_EDGE_H
#define CTOR_EDGE_H

#include <vector>

class Board;
class View;
class Player;

class Edge
{
    View* view;
    Board* board;
    bool road = false;
    Player* owner = nullptr;
    std::vector<int> adjacentVertexIndices;
    std::vector<int> adjacentEdgeIndices;
public:
    // Construct as an ordinary edge
    Edge(View* view, Board* board, std::vector<int> adjacentEdgeIndices, std::vector<int> adjacentVertexIndices);

    // Set this edge to a road without deducting resources.
    // If successful, return true. Otherwise, return false.
    // Should only be used for reading game from file.
    void setRoad(Player* roadOwner);

    void buildRoad(Player*); // Check if resource is sufficient, build, and deduct resources.
    bool isRoad() const;
    Player* getOwner() const;
};

#endif //CTOR_EDGE_H
