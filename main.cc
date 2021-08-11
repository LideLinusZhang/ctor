#include <iostream>
#include <sstream>
#include <memory>
#include <fstream>
#include "game.h"
#include "randomGen.h"
#include "fileMode.h"
#include "randomMode.h"

using namespace std;

const string defaultLayoutFileName = "layout.txt";

const string usage = "Available command-line options:\n"
                     "-seed xxx\n"
                     "  sets the random number generator’s seed to xxx.\n"
                     "-load xxx\n"
                     "  loads the game saved in file xxx.\n"
                     "-board xxx\n"
                     "  loads the game with the board specified in the file xxx instead of using random generation.\n"
                     "-random-board\n"
                     "  starts a game with a randomly generated board.";

enum GameMode
{
    Default,
    PureRandom,
    CustomLayout,
    LoadGame
};

int main(int argc, char *argv[])
{
    GameMode mode = GameMode::Default;
    string loadFileName, boardFileName;
    for (int i = 1; i < argc; i++)
    {
        string option(argv[i]);
        if (option == "-seed")
        {
            i++;
            Random::init(stoi(argv[i]));
        }
        else if (option == "-load")
        {
            if (mode == GameMode::Default || mode == GameMode::PureRandom)
            {
                mode = GameMode::LoadGame;
                i++;
                loadFileName = argv[i];
            }
            else
                i++;
        }
        else if (option == "-board")
        {
            if (mode == GameMode::Default || mode == GameMode::PureRandom)
            {
                mode = GameMode::CustomLayout;
                i++;
                boardFileName = argv[i];
            }
            else
                i++;
        }
        else if (option == "-random-board")
            mode = GameMode::PureRandom;
        else
        {
            cerr<<usage<<endl;
            return 22; // EINVAL: invalid argument.
        }
    }

    unique_ptr<Game> g;
    unique_ptr<BoardLayoutFactory> factory;

    ifstream file;
    file.exceptions(ifstream::badbit | ifstream::failbit);

    switch (mode)
    {
        case GameMode::PureRandom:
            factory = make_unique<RandomMode>();
            g = make_unique<Game>(move(factory));
            break;
        case GameMode::CustomLayout:
            file.open(boardFileName);
            factory = make_unique<FileMode>(file);
            g = make_unique<Game>(move(factory));
            file.close();
            break;
        case GameMode::LoadGame:
            g = make_unique<Game>(loadFileName);
            break;
        case GameMode::Default:
            file.open(defaultLayoutFileName);
            factory = make_unique<FileMode>(file);
            g = make_unique<Game>(move(factory));
            file.close();
            break;
    }

    bool continueGame = true;
    while (continueGame)
        continueGame = g->play();

    return 0;
}
