#include "board.h"
#include "view.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include "adjacencyTables.h"
#include "geese.h"
#include <sstream>

using namespace std;

Board::Board(View *view) : view{view}, geese{make_shared<Geese>()}
{
    for (int i =0;i<totalVertices;i++)
        vertices.push_back(std::make_shared<Vertex>(view, this, vertexAdjacentEdges[i], i));

    for (auto &i: edgeAdjacentVertexIdx)
    {
        std::vector<int> adjVertices(i, i + edgeAdjacentVertexNum);
        edges.push_back(std::make_shared<Edge>(view, this, adjVertices));
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
