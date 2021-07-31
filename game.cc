#include <utility>
#include <sstream>
#include "fairDice.h"
#include "loadedDice.h"
#include "player.h"
#include "game.h"
#include "boardFactory.h"
#include "view.h"
#include "board.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"

using namespace std;

Game::Game(istream &input) : input{input}
{
    input.exceptions(ios::eofbit | ios::failbit);

    loaded = make_unique<LoadedDice>(view.get());
    fair = make_unique<FairDice>();
}

Game::Game(const string &fileName, istream &input) : Game(input)
{
    read(fileName);
}

Game::Game(shared_ptr<BoardFactory> factory, istream &input) : Game(input)
{
    boardFactory = move(factory);
    gameBoard = boardFactory->createBoard(view.get());
    initPlayers();
}

void Game::initPlayers()
{
    for (int i = 0; i < totalPlayers; i++)
    {
        auto player = make_shared<Player>(view.get(), gameBoard.get(), static_cast<Color>(i));
        players.emplace_back(move(player));
    }
}

void Game::play()
{
    for (;; currentPlayerIndex = (currentPlayerIndex + 1) % 4)
    {
        Player *currentPlayer = players[currentPlayerIndex].get();

        try
        {
            beginTurn(currentPlayer);
            duringTurn(currentPlayer);
        }
        catch (ios_base::failure &)
        {
            save();
            return;
        }

        // TODO
    }
}

void Game::beginTurn(Player *player)
{
    ostringstream message;

    message << "Builder " << toString(player->getColor()) << "\'s turn." << endl;
    view->printMessage(message.str());

    int rollResult;
    try
    { rollResult = roll(); }
    catch (ios_base::failure &)
    { throw; }

    if (rollResult == 7)
        moveGeese(player);
    else
        obtainResources(rollResult);
}

void Game::obtainResources(int rollResult)
{
    vector<map<ResourceType, int>> resourcesSnapshot;

    for (int i = 0; i < totalPlayers; i++)
    {
        resourcesSnapshot.emplace_back(map<ResourceType, int>());
        for (int j = 0; j < resourceTypeCount; j++)
        {
            auto type = static_cast<ResourceType>(j);
            resourcesSnapshot[i].insert({type, players[i]->getResource(type)});
        }
    }

    for (int i = minTileIndex; i <= maxTileIndex; i++)
    {
        auto tile = gameBoard->getTile(i);

        if (tile->getValue() == rollResult)
            tile->obtainResource();
    }

    bool anyPlayerGainedResource = false;
    ostringstream message;

    for (int i = 0; i < totalPlayers; i++)
    {
        bool thisPlayerGainedResource = false;
        for (int j = 0; j < resourceTypeCount; j++)
        {
            auto type = static_cast<ResourceType>(j);
            // If a player gains resources, his current resource number
            // will not equal to the resource number in the snapshot.
            if (players[i]->getResource(type) != resourcesSnapshot[i][type])
            {
                int numGained = resourcesSnapshot[i][type] - players[i]->getResource(type);
                if (!thisPlayerGainedResource)
                {
                    thisPlayerGainedResource = true;
                    anyPlayerGainedResource = true;
                    auto color = static_cast<Color>(i);
                    message << "Builder " << color << " gained:" << endl;
                }

                message << numGained << " " << toStringAllCaps(type) << endl;
            }
        }
    }

    if (!anyPlayerGainedResource)
        message << "No builders gained resources." << endl;

    view->printMessage(message.str());
}

int Game::roll()
{
    string cmd;
    shared_ptr<Dice> dice(nullptr);
    int rollResult;

    while (true)
    {
        try
        { input >> cmd; }
        catch (ios_base::failure &)
        { throw; }

        if (cmd == "roll")
        {
            if (dice == nullptr)
                view->printError(ErrorType::InvalidRoll);
            else
            {
                try
                { rollResult = dice->roll(); }
                catch (ios_base::failure &)
                { throw; }
                break;
            }
        }
        else if (cmd == "load")
            dice = loaded;
        else if (cmd == "fair")
            dice = fair;
        else
            view->printError(ErrorType::InvalidCommand);
    }

    return rollResult;
}

void Game::duringTurn(Player *player)
{
    string cmd;
    string colorStr, takeStr, giveStr;
    string fileName;
    int index;

    while (true)
    {
        try
        { input >> cmd; }
        catch (ios_base::failure &)
        { throw; }

        if (cmd == "board")
            view->printBoard(gameBoard.get());
        else if (cmd == "status")
        {
            for (auto &p : players)
                p->printStatus();
        }
        else if (cmd == "residences")
            player->printResidences();
        else if (cmd == "build-road" || cmd == "build-res" || cmd == "improve")
        {
            try
            { input >> index; }
            catch (ios_base::failure &)
            {
                view->printError(ErrorType::InvalidOperation);
                continue;
            }

            if (cmd == "build-road")
                gameBoard->getEdge(index)->buildRoad(player);
            else if (cmd == "build-res")
                gameBoard->getVertex(index)->build(player);
            else
                gameBoard->getVertex(index)->improve(player);
        }
        else if (cmd == "trade")
        {
            try
            { input >> colorStr >> takeStr >> giveStr; }
            catch (ios_base::failure &)
            {
                view->printError(ErrorType::InvalidOperation);
                continue;
            }
            // TODO
        }
        else if (cmd == "next")
            return;
        else if (cmd == "save")
        {
            try
            { input >> fileName; }
            catch (ios_base::failure &)
            {
                view->printError(ErrorType::InvalidOperation);
                continue;
            }

            save(fileName);
        }
        else if (cmd == "help")
        {
            // TODO
        }
        else
            view->printError(ErrorType::InvalidCommand);
    }
}


