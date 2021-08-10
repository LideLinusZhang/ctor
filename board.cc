#include "board.h"
#include "view.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include "adjacencyTables.h"
#include "geese.h"
#include <sstream>

using namespace std;

Board::Board(View *view) : view{view}, geese{make_unique<Geese>()}
{
    for (int i = 0; i < totalVertices; i++)
        vertices.emplace_back(std::make_unique<Vertex>(view, this, i, vertexAdjacentEdges[i]));

    for (int i = 0; i < totalEdges; i++)
    {
        std::vector<int> adjVertices(edgeAdjacentVertexIdx[i], edgeAdjacentVertexIdx[i] + edgeAdjacentVertexNum);
        edges.emplace_back(std::make_unique<Edge>(view, this, i, adjVertices));
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

void Board::print() const
{
    view->printBoard(this);
}

std::string Board::toString() const
{
    ostringstream oss;

    for (int i = minTileIndex; i <= maxTileIndex; i++)
    {
        oss << static_cast<int>(tiles[i]->getType()) << " ";
        oss << tiles[i]->getValue();
        if (i != maxTileIndex)
            oss << " ";
    }

    return oss.str();
}

Geese *Board::getGeese() const
{
    return geese.get();
}

void Board::reset()
{
    int geesePosition = 0;
    for (int i = 0; i < totalTiles; i++)
    {
        if (tiles[i]->getType() == ResourceType::Park)
        {
            geesePosition = i;
            break;
        }
    }
    geese->setPosition(geesePosition);

    for (auto &v : vertices)
        v->reset();

    for (auto &e : edges)
        e->reset();
}