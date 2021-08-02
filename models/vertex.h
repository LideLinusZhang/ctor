#ifndef CTOR_VERTEX_H
#define CTOR_VERTEX_H

#include "../types/buildingType.h"
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
    Vertex(View* view, Board* board, std::vector<int> edgeIndices);
    Vertex(View* view, Board* board, Player* owner, BuildingType type, std::vector<int> edgeIndices);

    Player* getOwner() const;
    BuildingType getType() const;
    void build(Player* player); // Check if resource is sufficient, build, and deduct resources.
    void improve(Player* player); // Check if resource is sufficient, improve, and deduct resources.
};

#endif //CTOR_VERTEX_H
