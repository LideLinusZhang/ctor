#include "tile.h"
#include "board.h"
#include "vertex.h"
#include "player.h"
#include <sstream>

using namespace std;

Tile::Tile(Board* board, std::vector<int> vertices, ResourceType type, int value)
        :board(board), vertices(move(vertices)), type(type), value(value)
{

}

void Tile::obtainResource()
{
    // Add resources to all players who have building around this tile.
    for (int vertex : vertices)
    {
        Vertex *v = board->getVertex(vertex);
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

int Tile::getValue() const
{
    return value;
}

std::vector<Player*>
        Tile::getResidenceOwners()const {
    std::vector < Player * > re;
    for (int i = 0; i < vertices.size(); i++) {
        Player *p = board->getVertex(vertices[i])->getOwner();
        if (p != nullptr)
        {
            re.pushback(p);
        }
    }
    return re;
}



