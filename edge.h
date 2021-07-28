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
    int vertex1Index, vertex2Index;
    std::vector<int> adjacentEdgeIndices;
public:
    // Construct as an ordinary edge
    Edge(View* view, Board* board, std::vector<int> adjacentEdgeIndices, int vertex1Index, int vertex2Index);
    // Construct as a road (road = true)
    Edge(View* view, Board* board, Player* owner, std::vector<int> adjacentEdgeIndices, int vertex1Index,
         int vertex2Index);

    void buildRoad(Player*); // Check if resource is sufficient, build, and deduct resources.
    bool isRoad() const;
    Player* getOwner() const;
};

#endif //CTOR_EDGE_H
