#include "board.h"
#include "../view/view.h"
#include "edge.h"
#include "tile.h"
#include "vertex.h"
#include "../adjacencyTables.h"
#include <sstream>
#include <utility>

using namespace std;

Board::Board(View* view) : view{view} {
    for(auto &i : vertexAdjacentEdges) {
        vertices.push_back(std::make_shared<Vertex>(view,this, i));
    }
    for (int i=0;i<totalEdges;i++) {
        std::vector<int> adjVertices(edgeAdjacentVertexIdx[i], edgeAdjacentVertexIdx[i] + edgeAdjacentVertexNum);
        edges.push_back(std::make_shared<Edge>(view, this,  , adjVertices));
    }
    setBoard();
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
