#include "edge.h"
#include "player.h"

// Construct as an ordinary edge
Edge::Edge(View* view, Board* board, std::vector<int> adjacentEdgeIndices, int vertex1Index, int vertex2Index)
    :view(view), board(board), adjacentEdgeIndices(adjacentEdgeIndices), vertex1Index(vertex1Index), vertex2Index(vertex2Index)
{
    road = false;
    owner = nullptr;
}

// Construct as a road (road = true)
Edge::Edge(View* view, Board* board, Player* owner, std::vector<int> adjacentEdgeIndices, int vertex1Index,int vertex2Index)
    :view(view), board(board),owner(owner), adjacentEdgeIndices(adjacentEdgeIndices), vertex1Index(vertex1Index), vertex2Index(vertex2Index)
{
    road = true;    
}


void Edge::buildRoad(Player *p){
    if(road)
    {
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

}

inline bool Edge::isRoad() const{
    return road;
}

inline Player* Edge::getOwner() const{
    return owner;
}