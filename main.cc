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

            return 0;
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
