#ifndef CTOR_ADJACENCYTABLES_H
#define CTOR_ADJACENCYTABLES_H

#include <vector>
#include <memory>
#include "models/board.h"

const int tileSurroundingVertexNum = 6;
const int tileSurroundingVertexIdx[totalTiles][tileSurroundingVertexNum]{
        {0,  1,  3,  4,  8,  9},
        {2,  3,  7,  8,  13, 14},
        {4,  5,  9,  10, 15, 16},
        {6,  7,  12, 13, 18, 19},
        {8,  9,  14, 15, 20, 21},
        {10, 11, 16, 17, 22, 23},
        {13, 14, 19, 20, 25, 26},
        {15, 16, 21, 22, 27, 28},
        {18, 19, 24, 25, 30, 31},
        {20, 21, 26, 27, 32, 33},
        {22, 23, 28, 29, 34, 35},
        {25, 26, 31, 32, 37, 38},
        {27, 28, 33, 34, 39, 40},
        {30, 31, 36, 37, 42, 43},
        {32, 33, 38, 39, 44, 45},
        {34, 35, 40, 41, 46, 47},
        {37, 38, 43, 44, 49, 50},
        {39, 40, 45, 46, 51, 52},
        {44, 45, 49, 50, 52, 53}
};

const int edgeAdjacentVertexNum = 2;
const int edgeAdjacentVertexIdx[totalEdges][edgeAdjacentVertexNum]{
        {0,  1},
        {0,  3},
        {1,  4},
        {2,  3},
        {4,  5},
        {2,  7},
        {3,  8},
        {4,  9},
        {5,  10},
        {6,  7},
        {8,  9},
        {10, 11},
        {6,  12},
        {7,  13},
        {8,  14},
        {9,  15},
        {10, 16},
        {11, 17},
        {13, 14},
        {15, 16},
        {12, 18},
        {13, 19},
        {14, 20},
        {15, 21},
        {16, 22},
        {17, 23},
        {18, 19},
        {20, 21},
        {22, 23},
        {18, 24},
        {19, 25},
        {20, 26},
        {21, 27},
        {22, 28},
        {23, 29},
        {25, 26},
        {27, 28},
        {24, 30},
        {25, 31},
        {26, 32},
        {27, 33},
        {28, 34},
        {29, 35},
        {30, 31},
        {32, 33},
        {34, 35},
        {30, 36},
        {31, 37},
        {32, 38},
        {33, 39},
        {34, 40},
        {35, 41},
        {37, 38},
        {39, 40},
        {36, 42},
        {37, 43},
        {38, 44},
        {39, 45},
        {40, 46},
        {41, 47},
        {42, 43},
        {44, 45},
        {46, 47},
        {43, 48},
        {44, 49},
        {45, 50},
        {46, 51},
        {48, 49},
        {50, 51},
        {49, 52},
        {50, 53},
        {52, 53}
};


const std::vector<int> vertexAdjacentEdges[totalVertices]{
        std::vector<int>{0, 1},
        std::vector<int>{0, 2},
        std::vector<int>{3, 5},
        std::vector<int>{1, 3, 6},
        std::vector<int>{2, 4, 7},
        std::vector<int>{4, 8},
        std::vector<int>{9, 12},
        std::vector<int>{5, 9, 13},
        std::vector<int>{6, 10, 14},
        std::vector<int>{7, 10, 15},
        std::vector<int>{8, 11, 16},
        std::vector<int>{11, 17},
        std::vector<int>{12, 20},
        std::vector<int>{13, 18, 21},
        std::vector<int>{14, 18, 22},
        std::vector<int>{15, 19, 23},
        std::vector<int>{16, 19, 24},
        std::vector<int>{17, 25},
        std::vector<int>{20, 26, 29},
        std::vector<int>{21, 26, 30},
        std::vector<int>{22, 27, 31},
        std::vector<int>{23, 27, 32},
        std::vector<int>{24, 28, 33},
        std::vector<int>{25, 28, 34},
        std::vector<int>{29, 37},
        std::vector<int>{30, 35, 38},
        std::vector<int>{31, 35, 39},
        std::vector<int>{32, 36, 40},
        std::vector<int>{33, 36, 41},
        std::vector<int>{34, 42},
        std::vector<int>{37, 43, 46},
        std::vector<int>{38, 43, 47},
        std::vector<int>{39, 44, 48},
        std::vector<int>{40, 44, 49},
        std::vector<int>{41, 45, 50},
        std::vector<int>{42, 45, 51},
        std::vector<int>{46, 54},
        std::vector<int>{47, 52, 55},
        std::vector<int>{48, 52, 56},
        std::vector<int>{49, 53, 57},
        std::vector<int>{50, 53, 58},
        std::vector<int>{51, 59},
        std::vector<int>{54, 60},
        std::vector<int>{55, 60, 63},
        std::vector<int>{56, 61, 64},
        std::vector<int>{57, 61, 65},
        std::vector<int>{58, 62, 66},
        std::vector<int>{59, 62},
        std::vector<int>{63, 67},
        std::vector<int>{64, 67, 69},
        std::vector<int>{65, 68, 70},
        std::vector<int>{66, 68},
        std::vector<int>{69, 71},
        std::vector<int>{70, 71}
};
#endif //CTOR_ADJACENCYTABLES_H
