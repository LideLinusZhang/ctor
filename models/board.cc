#include "board.h"
#include "../view/view.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include <sstream>
#include <utility>

using namespace std;

Board::Board(View *view, std::vector<std::shared_ptr<Tile>> tiles,
             std::vector<std::shared_ptr<Edge>> edges,
             std::vector<std::shared_ptr<Vertex>> vertices,
             int geeseInitialPosition)
        : view{view}, tiles{std::move(tiles)}, edges{std::move(edges)}, vertices{std::move(vertices)},
          geese{geeseInitialPosition}
{
    setBoard();
}

void Board::setBoard()
{
    for (auto &it : tiles)
    {
        it->setBoard(this);
    }
    for (auto &it : vertices)
    {
        it->setBoard(this);
    }
    for (auto &it : edges)
    {
        it->setBoard(this);
    }
}

Tile *Board::getTile(int index) const
{
    return tiles[index].get();
}

Edge *Board::getEdge(int index) const
{
    return edges[index].get();
}

Vertex *Board::getVertex(int index) const
{
    return vertices[index].get();
}

bool Board::tryMoveGeese(int tileIndex)
{
    return geese.tryMoveTo(tileIndex);
}

void Board::print() const
{
    view->printBoard(this);
}

std::string Board::toString() const
{
    ostringstream oss;

    for(int i = minTileIndex; i<=maxTileIndex;i++)
    {
        oss<<i<<" ";
        oss<<static_cast<int>(tiles[i]->getType())<<" ";
        oss<<tiles[i]->getValue();
        if(i!=maxTileIndex)
            oss<<" ";
    }

    return oss.str();
}

int Board::getGeesePosition() const
{
    return geese.getPosition();
}
