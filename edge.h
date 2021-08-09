#ifndef CTOR_EDGE_H
#define CTOR_EDGE_H

#include <vector>

class Board;

class View;

class Player;

class Edge
{
    const View *view;
    const Board *board;
    const int index;
    bool road = false;
    Player *owner = nullptr;
    const std::vector<int> adjacentVertexIndices;
public:
    // Construct as an ordinary edge
    Edge(View *view, Board *board, int index, std::vector<int> adjacentVertexIndices);

    // Set this edge to a road without deducting resources.
    // If successful, return true. Otherwise, return false.
    // Should only be used for reading game from file.
    void setRoad(Player *roadOwner);
    // Check if resource is sufficient, build, and deduct resources.
    void buildRoad(Player *player);
    // Reset this edge by removing the road on it.
    void reset();

    bool isRoad() const;
    Player *getOwner() const;
    const std::vector<int> &getAdjacentVertexIdx() const;
};

#endif //CTOR_EDGE_H