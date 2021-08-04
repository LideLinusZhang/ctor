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
    for (int i = 0; i < argc; i++)
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
                loadFileName = argv[i + 1];
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
                loadFileName = argv[i];
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

    shared_ptr<Game> g;
    shared_ptr<BoardLayoutFactory> factory;

    do
    {
        ifstream file;
        switch (mode)
        {
            case GameMode::PureRandom:
                factory = make_shared<RandomMode>();
                g = make_shared<Game>(factory);
                break;
            case GameMode::CustomLayout:
                file.open(boardFileName);
                factory = make_shared<FileMode>(file);
                g = make_shared<Game>(factory);
                file.close();
                break;
            case GameMode::LoadGame:
                g = make_shared<Game>(loadFileName);
                break;
            case GameMode::Default:
                file.open(defaultLayoutFileName);
                factory = make_shared<FileMode>(file);
                g = make_shared<Game>(factory);
                file.close();
                break;
        }
    } while (!g->play());

    return 0;
}
