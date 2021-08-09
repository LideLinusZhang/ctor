#ifndef CTOR_TILE_H
#define CTOR_TILE_H

#include "resourceType.h"
#include "color.h"
#include <vector>

class Board;

class Player;

const int parkValue = 7;

class Tile
{
    const Board *board;
    const std::vector<int> vertices;
    const ResourceType type;
    const int index;
    const int value; // value = 7 for Park
public:
    Tile(Board *board, std::vector<int> vertices, ResourceType type, int index, int value);

    void obtainResource(); // Add resources to all players who have building around this tile.
    ResourceType getType() const;
    int getValue() const;
    // Return a list that contains the players that have residences on this tile.
    // The list should be duplicate-free and sorted.
    std::vector<Player *> getResidenceOwners() const;
};

#endif //CTOR_TILE_H