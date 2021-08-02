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

    std::vector<int> adjacentEdgeIndices;
public:
    // Construct as an ordinary edge
    Edge(View* view, std::vector<int> adjacentEdgeIndices);
    // Construct as a road (road = true)
    Edge(View* view, Player* owner, std::vector<int> adjacentEdgeIndices);

    void setBoard(Board *);
    std::vector<int> getadjacentEdgeIndices() const;

    void buildRoad(Player*); // Check if resource is sufficient, build, and deduct resources.
    bool isRoad() const;
    Player* getOwner() const;
};

#endif //CTOR_EDGE_H