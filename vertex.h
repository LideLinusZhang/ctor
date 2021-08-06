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
    int index;
    Player* owner = nullptr;
    BuildingType type = BuildingType::None;
    const std::vector<int> &edgeIndices;

    // Check if the player has a road adjacent to this vertex.
    bool hasAdjacentRoad(Player *player) const;
    // Check if this building is adjacent to any building.
    bool isAdjacentToBuilding() const;
public:
    Vertex(View* view, Board* board, const std::vector<int> & edgeIndices, int index);

    // Try to set this vertex to a building without deducting resources.
    // If successful, return true. Otherwise, return false.
    // Should only be used for setting initial residences at the beginning of a game.
    bool trySetBuilding(BuildingType buildingType, Player* buildingOwner);
    // Set this vertex to a building without deducting resources.
    // Should only be used for reading game from file.
    void setBuilding(BuildingType buildingType, Player* buildingOwner);

    const std::vector<int> &getEdgeIndices() const;
    Player* getOwner() const;
    BuildingType getType() const;

    void build(Player* player); // Check if resource is sufficient, build, and deduct resources.
    void improve(Player* player); // Check if resource is sufficient, improve, and deduct resources.
};
#endif //CTOR_VERTEX_H
