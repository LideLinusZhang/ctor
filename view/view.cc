#include "view.h"
#include "boardPrinters.h"
#include <iostream>
#include <iomanip>
#include <sstream>

using namespace std;

View::View(ostream &output, ostream &error) : output{output}, error{error} {}

void View::printMessage(const string &message) const
{
    output << message << endl;
}

void View::printPrompt(const string &prompt) const
{
    output << prompt << endl << "¿ ";
}

void View::printError(ErrorType type) const
{
    switch (type)
    {
        case ErrorType::InvalidBuildOrImprove:
            error << "You cannot build here." << endl;
            break;
        case ErrorType::InvalidRoll:
            error << "Invalid roll." << endl;
            break;
        case ErrorType::InvalidCommand:
            error << "Invalid command." << endl;
            break;
        case ErrorType::InsufficientResource:
            error << "You do not have enough resources." << endl;
            break;
        case ErrorType::InvalidInput:
            error << "Invalid input." << endl;
    }
}

string spaces(int total)
{
    ostringstream oss;
    for (int i = 0; i < total; i++)
        oss << " ";
    return oss.str();
}

void View::printBoard(const Board *board) const
{
    const int totalLines = 41;
    const int rowHeight = 8;

    int curTileIdx = 0;
    int curEdgeIdx = 0;
    int curVertexIdx = 0;

    int totalSymbols, totalBlocks, totalSpaces;

    for (int i = 0; i < totalLines; i++)
    {
        if ((0 <= i && i <= 3) || (37 <= i && i <= 40))
        {
            totalSymbols = 2;
            totalBlocks = 1;
            totalSpaces = 20;
        }
        else if ((4 <= i && i <= 7) || (33 <= i && i <= 36))
        {
            totalSymbols = 4;
            totalBlocks = 3;
            totalSpaces = 10;
        }
        else
        {
            totalSymbols = 6;
            totalBlocks = 5;
            totalSpaces = 0;
        }


        int j = i % rowHeight;

        if (i == 4 || i == 36 || j == 0)
        {
            output << spaces(totalSpaces)
                   << generateLineMode1(curVertexIdx, curEdgeIdx, curTileIdx, totalBlocks, board);
        }
        else if (i == 39 || j == 1 || j == 5)
        {
            output << spaces(totalSpaces)
                   << generateLineMode3(totalSymbols);
        }
        else if (i == 6 || (j == 2 && i != 34))
        {
            output << spaces(totalSpaces)
                   << generateLineMode6(curEdgeIdx, curTileIdx, totalBlocks, board);
        }
        else if (i == 7 || (j == 3 && i != 35))
        {
            output << spaces(totalSpaces)
                   << generateLineMode4(curTileIdx, totalBlocks, board);
        }
        else if (j == 4)
        {
            output << spaces(totalSpaces)
                   << generateLineMode2(curVertexIdx, curEdgeIdx, curTileIdx, totalBlocks, board);
        }
        else if (i == 34 || j == 6)
        {
            output << spaces(totalSpaces)
                   << generateLineMode7(curEdgeIdx, curTileIdx, totalBlocks, board);
        }
        else if (i == 35 || j == 7)
        {
            output << spaces(totalSpaces)
                   << generateLineMode5(curTileIdx, totalBlocks, board);
        }

        output << endl;
    }
}


