#include "edge.h"
#include "view.h"
#include "board.h"
#include "player.h"
#include "vertex.h"

using namespace std;

// Construct as an ordinary edge
Edge::Edge(View *view, Board *board, int index, vector<int> adjacentVertexIndices)
        : view(view), board(board), index{index}, adjacentVertexIndices(std::move(adjacentVertexIndices)) {}

void Edge::buildRoad(Player *p)
{
    if (road)
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }

    bool is_link = false;
    for (int i : adjacentVertexIndices)
    {
        Vertex *v = board->getVertex(i);
        if (v->getOwner() == p)
        {
            is_link = true;
            break;
        }
        std::vector<int> vEdgeIndices = v->getEdgeIndices();
        for (int j : vEdgeIndices)
        {
            Edge *e = board->getEdge(j);
            if (e != this && e->getOwner() == p)
            {
                is_link = true;
                break;
            }
        }
        if (is_link)
            break;
    }

    if (!is_link)
    {
        view->printError(ErrorType::InvalidBuildOrImprove);
        return;
    }

    //cost one WiFi and one HEAT
    int wifi_num = p->getResource(ResourceType::WiFi);
    int heat_num = p->getResource(ResourceType::Heat);
    if (wifi_num >= 1 && heat_num >= 1)
    {
        setRoad(p);
        p->addRoad(index);

        p->setResource(ResourceType::WiFi, --wifi_num);
        p->setResource(ResourceType::Heat, --heat_num);
    }
    else
        view->printError(ErrorType::InsufficientResource);
}

bool Edge::isRoad() const
{
    return road;
}

Player *Edge::getOwner() const
{
    return owner;
}

void Edge::setRoad(Player *roadOwner)
{
    road = true;
    owner = roadOwner;
}

const std::vector<int> &Edge::getAdjacentVertexIdx() const
{
    return adjacentVertexIndices;
}

void Edge::reset()
{
    owner = nullptr;
    road = false;
}
