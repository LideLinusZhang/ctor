#include <iostream>
#include <sstream>
#include <memory>
#include "controller/game.h"
#include "random/random.h"
#include "boardFactory/fileMode.h"
#include "boardFactory/randomMode.h"


using namespace std;

int main(int argc, char *argv[])
{
    bool load = false;
    bool board = false;
    bool random = false;
    string loadFile;
    string boardFile;
    shared_ptr<Game> g;
    for (int i = 0; i < argc; i += 2) {
        if (argv[i] == "-seed") {
            Random::init(stoi(argv[i + 1]));
        }
        if (argv[i] == "-load") {
            load = true;
            loadFile = argv[i + 1];
        } else if (argv[i] == "-board") {
            board = true;
            boardFile = argv[i + 1];
        } else if (argv[i] == "-random-board") {
            random = true;
        }
    }
    if (load) {
        g = make_shared<Game>(loadFile);
    } else if (board) {
        istringstream file(boardFile);
        shared_ptr<BoardLayoutFactory> factory = make_shared<FileMode>(file);
        g = make_shared<Game>(factory);
    } else {
        shared_ptr<BoardLayoutFactory> factory = make_shared<RandomMode>();
        g = make_shared<Game>(factory);
    }
    if (!g->play()) {
        return 0;
    }
}
