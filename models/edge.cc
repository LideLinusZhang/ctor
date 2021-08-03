#include "edge.h"
#include "../view/view.h"
#include <utility>
#include "player.h"

using namespace std;

// Construct as an ordinary edge
Edge::Edge(View *view, Board *board, vector<int> adjacentVertexIndices)
        : view(view), board(board), adjacentVertexIndices(std::move(adjacentVertexIndices))
{
    road = false;
    owner = nullptr;
}


void Edge::buildRoad(Player *p)
{
    if (road)
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }
    //cost one WiFi and one HEAT
    int wifi_num = p->getResource(ResourceType::WiFi);
    int heat_num = p->getResource(ResourceType::Heat);
    if (wifi_num >= 1 && heat_num >= 1)
    {
        owner = p;
        road = true;
        p->setResource(ResourceType::WiFi, --wifi_num);
        p->setResource(ResourceType::Heat, --heat_num);
    }

}

inline bool Edge::isRoad() const
{
    return road;
}

inline Player *Edge::getOwner() const
{
    return owner;
}

void Edge::setRoad(Player *roadOwner)
{
    road = true;
    owner = roadOwner;
}
