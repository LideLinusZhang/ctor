#include "edge.h"
#include "player.h"
#include "view.h"

// Construct as an ordinary edge
Edge::Edge(View* view, std::vector<int> adjacentEdgeIndices)
        :view(view), adjacentEdgeIndices(adjacentEdgeIndices)
{
    road = false;
    owner = nullptr;
    board = nullptr;
}

// Construct as a road (road = true)
Edge::Edge(View* view, Player* owner, std::vector<int> adjacentEdgeIndices)
        :view(view),owner(owner), adjacentEdgeIndices(adjacentEdgeIndices)
{
    road = true;
    board = nullptr;
}

void Edge::setBoard(Board *b){
    board = b;
}

void Edge::buildRoad(Player *p){
    if(road)
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }
    //cost one WiFi and one HEAT
    int wifi_num = p->getResource(ResourceType::WiFi);
    int heat_num = p->getResource(ResourceType::Heat);
    if (wifi_num>=1 && heat_num>=1)
    {
        owner = p;
        road = true;
        p->setResource(ResourceType::WiFi, --wifi_num);
        p->setResource(ResourceType::Heat, --heat_num);
    }
    else
    {
        view->printError(ErrorType::InsufficientResource);
    }

}

inline bool Edge::isRoad() const{
    return road;
}

inline Player* Edge::getOwner() const{
    return owner;
}


std::vector<int> Edge::getadjacentEdgeIndices() const{
    return adjacentEdgeIndices;
}