#ifndef CTOR_TILE_H
#define CTOR_TILE_H

#include "resourceType.h"
#include "color.h"
#include <vector>

class Board;

class Player;

class Tile
{
    Board* board;
    std::vector<int> vertices;
    ResourceType type;
    int value;
public:
    Tile(std::vector<int> vertices, ResourceType type, int value);

    void obtainResource(); // Add resources to all players who have building around this tile.
    ResourceType getType() const;
    void setBoard(Board *);
    int getValue() const;
    // Return a list that contains the players that have residences on this tile.
    // The list should be duplicate-free and sorted.
    std::vector<Player*> getResidenceOwners() const;
};

#endif //CTOR_TILE_H