#include "board.h"
#include "../view/view.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include <sstream>
#include <utility>

using namespace std;

Board::Board(View* view, std::vector<std::shared_ptr<Tile>> tiles)
            : view{view}, tiles{std::move(tiles)} {
    for(auto i : vertexAdjacentEdges) {
        vertices.push_back(std::make_shared<Vertex>(view, i));
    }
    for (int i = 0; i < 71; i++) {
        std::vector<int> v(edgeAdjacentVertices[i], edgeAdjacentVertices[i] + 2);
        edges.push_back(std::make_shared<Edge>(view, v));
    }
    for (int i = 0; i < tiles.size(); i++) {
        if (tiles[i]->getType() == Park) {
            geese = std::make_shared<Geese>(i);
        }
    }      
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

Geese* Board::getGeese() const
{
    return geese.get();
}
