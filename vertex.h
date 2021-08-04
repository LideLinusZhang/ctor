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
    Vertex(View* view, Board* board, std::vector<int> edgeIndices);

    // Try to set this vertex to a building without deducting resources.
    // If successful, return true. Otherwise, return false.
    // Should only be used for setting initial residences at the beginning of a game.
    bool trySetBuilding(BuildingType buildingType, Player* buildingOwner);
    // Set this vertex to a building without deducting resources.
    // Should only be used for reading game from file.
    void setBuilding(BuildingType buildingType, Player* buildingOwner);

    Player* getOwner() const;
    BuildingType getType() const;
    void build(Player* player); // Check if resource is sufficient, build, and deduct resources.
    void improve(Player* player); // Check if resource is sufficient, improve, and deduct resources.
};
#endif //CTOR_VERTEX_H