#include "boardPrinters.h"
#include "board.h"
#include "tile.h"
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

string generateLineMode1(int &vertexIdx, int &edgeIdx, int &tileIdx, int totalBlocks, Board* board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for(int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if(j==0||j==4)
        {
            line<<"|"<<setw(2)<<vertexIdx<<"|";
            vertexIdx++;
        }
        else if(j==1||j==3)
            line<<"--";
        else if(j==2)
        {
            line<<setw(2)<<edgeIdx;
            edgeIdx++;
        }
        else if(j==5||j==7)
            line<<"  ";
        else
        {
            line<<setw(2)<<board->getTile(tileIdx)->getValue();
            tileIdx++;
        }
    }
    return line.str();
}

string generateLineMode2(int &vertexIdx, int &edgeIdx, int &tileIdx, int totalBlocks, Board* board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for(int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if(j==0||j==4)
        {
            line<<"|"<<setw(2)<<vertexIdx<<"|";
            vertexIdx++;
        }
        else if(j==1||j==3)
            line<<"  ";
        else if(j==2)
        {
            line<<setw(2)<<board->getTile(tileIdx)->getValue();
            tileIdx++;
        }
        else if(j==5||j==7)
            line<<"--";
        else
        {
            line<<setw(2)<<edgeIdx;
            edgeIdx++;
        }
    }
    return line.str();
}

string generateLineMode3(int totalSymbols)
{
    ostringstream line;
    line<<setw(3)<<"|";
    for(int i = 1;i<totalSymbols;i++)
        line<<setw(10)<<"|";
    return line.str();
}

string generateLineMode4(int tileIdx, int totalBlocks, Board* board)
{
    ostringstream line;
    line<<setw(3)<<"|";
    for(int i = 0; i < totalBlocks; i++)
    {
        if(i%2==0)
        {
            line<<"  "<<left<<setw(7)<<toStringAllCaps(board->getTile(tileIdx)->getType());
            line<<"|";
            tileIdx++;
        }
        else
            line<<right<<setw(10)<<"|";
    }
    return line.str();
}

string generateLineMode5(int tileIdx, int totalBlocks, Board* board)
{
    ostringstream line;
    line<<setw(3)<<"|";
    for(int i = 0; i < totalBlocks; i++)
    {
        if(i%2!=0)
        {
            line<<"  "<<left<<setw(7)<<toStringAllCaps(board->getTile(tileIdx)->getType());
            line<<"|";
            tileIdx++;
        }
        else
            line<<right<<setw(10)<<"|";
    }
    return line.str();
}

string generateLineMode6(int &edgeIdx, int tileIdx, int totalBlocks, Board* board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for(int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if(j==0||j==4)
        {
            line<<" "<<setw(2)<<edgeIdx<<" ";
            edgeIdx++;
        }
        else if(j==2)
        {
            line<<setw(2)<<tileIdx;
            tileIdx++;
        }
        else
            line<<"  ";
    }
    return line.str();
}

std::string generateLineMode7(int &edgeIdx, int tileIdx, int totalBlocks, Board* board)
{
    ostringstream line;
    const int totalElements = 4 * totalBlocks + 1;

    for(int i = 0; i < totalElements; i++)
    {
        int j = i % 8;
        if(j==0||j==4)
        {
            line<<" "<<setw(2)<<edgeIdx<<" ";
            edgeIdx++;
        }
        else if(j==6)
        {
            line<<setw(2)<<tileIdx;
            tileIdx++;
        }
        else
            line<<"  ";
    }
    return line.str();
}
