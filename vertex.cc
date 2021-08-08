#include "vertex.h"
#include "view.h"
#include "board.h"
#include "player.h"
#include "edge.h"
#include <algorithm>
#include <utility>

using namespace std;

Vertex::Vertex(View *view, Board *board, int index, const std::vector<int> &edgeIndices)
        : view(view), board(board), index{index}, edgeIndices(edgeIndices) {}

Player *Vertex::getOwner() const
{
    return owner;
}

BuildingType Vertex::getType() const
{
    return type;
}

const std::vector<int> &Vertex::getEdgeIndices() const
{
    return edgeIndices;
}

void Vertex::build(Player *player)
{
    if (type != BuildingType::None || !hasAdjacentRoad(player) || isAdjacentToBuilding())
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }
    //cost one BRICK, one ENERGY, one GLASS, and one WIFI
    int brick_num = player->getResource(ResourceType::Brick);
    int energy_num = player->getResource(ResourceType::Energy);
    int glass_num = player->getResource(ResourceType::Glass);
    int wifi_num = player->getResource(ResourceType::WiFi);

    if (brick_num >= 1 && energy_num >= 1 && glass_num >= 1 && wifi_num >= 1)
    {
        setBuilding(BuildingType::Basement, player);

        player->addBuilding(index);

        player->setResource(ResourceType::Brick, --brick_num);
        player->setResource(ResourceType::Energy, --energy_num);
        player->setResource(ResourceType::Glass, --glass_num);
        player->setResource(ResourceType::WiFi, --wifi_num);
    }
    else
        view->printError(ErrorType::InsufficientResource);
}

void Vertex::improve(Player *player)
{
    if (BuildingType::None == type || BuildingType::Tower == type || player != owner)
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }

    if (BuildingType::Basement == type)
    {
        //cost two GLASS, and three HEAT
        int glass_num = player->getResource(ResourceType::Glass);
        int heat_num = player->getResource(ResourceType::Heat);
        if (glass_num >= 2 && heat_num >= 3)
        {
            type = BuildingType::House;

            player->setResource(ResourceType::Glass, glass_num - 2);
            player->setResource(ResourceType::Heat, heat_num - 3);
        }
        else
            view->printError(ErrorType::InsufficientResource);
    }
    else if (BuildingType::House == type)
    {
        //cost three BRICK, two ENERGY, two GLASS, one WIFI, and two HEAT
        int brick_num = player->getResource(ResourceType::Brick);
        int energy_num = player->getResource(ResourceType::Energy);
        int glass_num = player->getResource(ResourceType::Glass);
        int wifi_num = player->getResource(ResourceType::WiFi);
        int heat_num = player->getResource(ResourceType::Heat);

        if (brick_num >= 3 && energy_num >= 2 && glass_num >= 2 && wifi_num >= 1 && heat_num >= 2)
        {
            type = BuildingType::Tower;

            player->setResource(ResourceType::Brick, brick_num - 3);
            player->setResource(ResourceType::Energy, energy_num - 2);
            player->setResource(ResourceType::Glass, glass_num - 2);
            player->setResource(ResourceType::WiFi, wifi_num - 1);
            player->setResource(ResourceType::Heat, heat_num - 2);
        }
        else
            view->printError(ErrorType::InsufficientResource);
    }
}

bool Vertex::trySetBuilding(BuildingType buildingType, Player *buildingOwner)
{
    if (this->type != BuildingType::None || isAdjacentToBuilding())
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return false;
    }

    setBuilding(buildingType, buildingOwner);
    buildingOwner->addBuilding(index);
    return true;
}

void Vertex::setBuilding(BuildingType buildingType, Player *buildingOwner)
{
    type = buildingType;
    owner = buildingOwner;
}

bool Vertex::hasAdjacentRoad(Player *player) const
{
    if (std::any_of(edgeIndices.begin(), edgeIndices.end(),
                    [player, this](int i) -> bool { return board->getEdge(i)->getOwner() == player; }))
        return true;
    else
        return false;
}

bool Vertex::isAdjacentToBuilding() const
{
    vector<int> adjacentVertexIdx;

    for (auto i : edgeIndices)
    {
        Edge *edge = board->getEdge(i);
        for (auto j : edge->getAdjacentVertexIdx())
        {
            if (j != index)
                adjacentVertexIdx.push_back(j);
        }
    }

    if (std::any_of(adjacentVertexIdx.begin(), adjacentVertexIdx.end(),
                    [this](int i) -> bool { return board->getVertex(i)->getType() != BuildingType::None; }))
        return true;
    else
        return false;
}

void Vertex::reset()
{
    type = BuildingType::None;
    owner = nullptr;
}
