#include "boardPrinters.h"
#include "../models/board.h"
#include "../models/tile.h"
#include "../models/edge.h"
#include "../models/vertex.h"
#include "../models/player.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string getEdgeString(int edgeIdx, const Board *board)
{
    ostringstream oss;
    Edge *edge = board->getEdge(edgeIdx);
    if (edge->isRoad())
        oss << toChar(edge->getOwner()->getColor()) << "R";
    else
        oss << setw(2) << edgeIdx;
    return oss.str();
}

string getVertexString(int vertexIdx, const Board *board)
{
    ostringstream oss;
    Vertex *vertex = board->getVertex(vertexIdx);
    if (vertex->getType() != BuildingType::None)
        oss << toChar(vertex->getOwner()->getColor()) << toChar(vertex->getType());
    else
        oss << setw(2) << vertexIdx;
    return oss.str();
}

string getTileValueString(int tileIdx, const Board *board)
{
    ostringstream oss;
    Tile *tile = board->getTile(tileIdx);
    if (tile->getType() == ResourceType::Park)
        oss << "  ";
    else
        oss << setw(2) << tile->getValue();
    return oss.str();
}

string generateLineMode1(int &vertexIdx, int &edgeIdx, int tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for (int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if (j == 0 || j == 4)
        {
            line << "|" << getVertexString(vertexIdx, board) << "|";
            vertexIdx++;
        }
        else if (j == 1 || j == 3)
            line << "--";
        else if (j == 2)
        {
            line << getEdgeString(edgeIdx, board);
            edgeIdx++;
        }
        else if (j == 5 || j == 7)
            line << "  ";
        else
        {
            line << getTileValueString(tileIdx, board);
            tileIdx++;
        }
    }
    return line.str();
}

string generateLineMode2(int &vertexIdx, int &edgeIdx, int tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for (int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if (j == 0 || j == 4)
        {
            line << "|" << getVertexString(vertexIdx, board) << "|";
            vertexIdx++;
        }
        else if (j == 1 || j == 3)
            line << "  ";
        else if (j == 2)
        {
            line << getTileValueString(tileIdx, board);;
            tileIdx++;
        }
        else if (j == 5 || j == 7)
            line << "--";
        else
        {
            line << getEdgeString(edgeIdx, board);
            edgeIdx++;
        }
    }
    return line.str();
}

string generateLineMode3(int &tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    line << setw(3) << "|";
    for (int i = 0; i < totalBlocks; i++)
    {
        if (i % 2 == 0)
        {
            if (board->getGeese()->getPosition() == tileIdx)
                line << "  GEESE  |";
            else
                line << setw(10) << "|";
            tileIdx++;
        }
        else
            line << setw(10) << "|";
    }
    return line.str();
}

string generateLineMode4(int &tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    line << setw(3) << "|";
    for (int i = 0; i < totalBlocks; i++)
    {
        if (i % 2 == 1)
        {
            if (board->getGeese()->getPosition() == tileIdx)
                line << "  GEESE  |";
            else
                line << setw(10) << "|";
            tileIdx++;
        }
        else
            line << setw(10) << "|";
    }
    return line.str();
}

string generateLineMode5(int tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    line << setw(3) << "|";
    for (int i = 0; i < totalBlocks; i++)
    {
        if (i % 2 == 0)
        {
            line << "  " << left << setw(7) << toStringAllCaps(board->getTile(tileIdx)->getType());
            line << "|";
            tileIdx++;
        }
        else
            line << right << setw(10) << "|";
    }
    return line.str();
}

string generateLineMode6(int tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    line << setw(3) << "|";
    for (int i = 0; i < totalBlocks; i++)
    {
        if (i % 2 != 0)
        {
            line << "  " << left << setw(7) << toStringAllCaps(board->getTile(tileIdx)->getType());
            line << "|";
            tileIdx++;
        }
        else
            line << right << setw(10) << "|";
    }
    return line.str();
}

string generateLineMode7(int &edgeIdx, int tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for (int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if (j == 0 || j == 4)
        {
            line << " " << getEdgeString(edgeIdx, board) << " ";
            edgeIdx++;
        }
        else if (j == 2)
        {
            line << setw(2) << tileIdx;
            tileIdx++;
        }
        else
            line << "  ";
    }
    return line.str();
}

std::string generateLineMode8(int &edgeIdx, int tileIdx, int totalBlocks, const Board *board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for (int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if (j == 0 || j == 4)
        {
            line << " " << getEdgeString(edgeIdx, board) << " ";
            edgeIdx++;
        }
        else if (j == 6)
        {
            line << setw(2) << tileIdx;
            tileIdx++;
        }
        else
            line << "  ";
    }
    return line.str();
}
