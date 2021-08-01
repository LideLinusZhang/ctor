#ifndef CTOR_BOARDPRINTERS_H
#define CTOR_BOARDPRINTERS_H

#include <string>

// Mode 1:  "| 6|-- 9--| 7|  10  | 8|--10--| 9|   5  |10|--11--|11|"
// Mode 2:  "|24|   8  |25|--35--|26|   2  |27|--36--|28|   6  |29|"
// Mode 3:  "  |         |"
// Mode 4:  "  |  ENERGY |         |  PARK   |         |  HEAT   |"
// Mode 5:  "  |         |  GLASS  |         |  BRICK  |         |"
// Mode 6:  " 12    3   13        14    4   15        16    5   17"
// Mode 7:  " 20        21    6   22        23    7   24        25

class Board;

std::string generateLineMode1(int &vertexIdx, int &edgeIdx, int &tileIdx, int totalBlocks, Board* board);
std::string generateLineMode2(int &vertexIdx, int &edgeIdx, int &tileIdx, int totalBlocks, Board* board);

std::string generateLineMode3(int totalSymbols);

std::string generateLineMode4(int tileIdx, int totalBlocks, Board* board);
std::string generateLineMode5(int tileIdx, int totalBlocks, Board* board);

std::string generateLineMode6(int &edgeIdx, int tileIdx, int totalBlocks, Board* board);
std::string generateLineMode7(int &edgeIdx, int tileIdx, int totalBlocks, Board* board);

#endif //CTOR_BOARDPRINTERS_H
