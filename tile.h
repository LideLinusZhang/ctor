#ifndef CTOR_TILE_H
#define CTOR_TILE_H

#include "resourceType.h"
#include <vector>

class Board;

class Tile
{
    Board* board;
    std::vector<int> vertices;
    ResourceType type;
public:
    Tile(Board* board, std::vector<int> vertices, ResourceType type);

    void obtainResource(); // Add resources to all players who have building around this tile.
    ResourceType getType() const;
};

#endif //CTOR_TILE_H
