#include "tile.h"
#include "board.h"
#include "vertex.h"
#include "player.h"
#include "buildingType.h"
#include "geese.h"
#include <sstream>
#include <algorithm>

using namespace std;

Tile::Tile(Board *board, std::vector<int> vertices, ResourceType type, int index, int value)
        : board(board), vertices(move(vertices)), type(type), index{index}, value(value) {}

void Tile::obtainResource()
{
    // If geese is on this tile, no resource can be obtained.
    if (board->getGeese()->getPosition() == index)
        return;

    // Add resources to all players who have building around this tile.
    for (int vertex : vertices)
    {
        Vertex *v = board->getVertex(vertex);
        if (nullptr == v->getOwner())
        {
            continue;
        }
        // one for basement, two for house, three for tower
        int source_num = v->getOwner()->getResource(type);
        BuildingType b_type = v->getType();
        v->getOwner()->setResource(type, source_num + b_type);
    }
}

ResourceType Tile::getType() const
{
    return type;
}

int Tile::getValue() const
{
    return value;
}

std::vector<Player *> Tile::getResidenceOwners() const
{
    std::vector<Player *> owners;

    for (int i : vertices)
    {
        Player *player = board->getVertex(i)->getOwner();

        if (player == nullptr)
            continue;

        bool isDupe = any_of(owners.begin(), owners.end(),
                             [player](Player *other) -> bool { return other == player; });
        if (!isDupe)
            owners.push_back(player);
    }

    sort(owners.begin(), owners.end(), [](const Player *a, const Player *b) -> bool {
        return a->getColor() < b->getColor();
    });

    return owners;
}

