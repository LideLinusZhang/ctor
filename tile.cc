#include "tile.h"
#include "board.h"
#include "vertex.h"
#include "player.h"

Tile::Tile(Board* board, std::vector<int> vertices, ResourceType type)
    :board(board), vertices(vertices), type(type)
{

}

void Tile::obtainResource()
{
    // Add resources to all players who have building around this tile.
    for (size_t i = 0; i < vertices.size(); i++)
    {
        Vertex *v = board->getVertex(vertices[i]);
        if(nullptr == v->getOwner())
        {
            continue;
        }
        // one for basement, two for house, three for tower
        int source_num =  v->getOwner()->getResource(type);
        BuildingType b_type = v->getType();
        v->getOwner()->setResource(type, source_num + b_type);

    }
    
}

inline ResourceType Tile::getType() const
{
    return type;
}