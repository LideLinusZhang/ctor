#ifndef CTOR_VERTEX_H
#define CTOR_VERTEX_H

#include "buildingType.h"
#include <vector>

class View;
class Board;
class Player;

class Vertex
{
    View* view;
    Board* board;
    Player* owner = nullptr;
    BuildingType type = BuildingType::None;
    std::vector<int> edgeIndices;
public:
    Vertex(View* view, std::vector<int> edgeIndices);
    Vertex(View* view, Player* owner, BuildingType type, std::vector<int> edgeIndices);

    std::vector<int> getedgeIndices() const;
    void setBoard(Board *);
    Player* getOwner() const;
    BuildingType getType() const;
    void build(Player* player); // Check if resource is sufficient, build, and deduct resources.
    void improve(Player* player); // Check if resource is sufficient, improve, and deduct resources.
};

#endif //CTOR_VERTEX_H