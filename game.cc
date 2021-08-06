#include <utility>
#include <sstream>
#include <fstream>
#include <stdexcept>
#include "fairDice.h"
#include "loadedDice.h"
#include "player.h"
#include "game.h"
#include "boardLayoutFactory.h"
#include "fileMode.h"
#include "view.h"
#include "board.h"
#include "tile.h"
#include "vertex.h"
#include "edge.h"
#include "geese.h"

using namespace std;

const string helpMessage = "Valid commands:\n"
                           "board\n"
                           "status\n"
                           "residences\n"
                           "build-road <edge#>\n"
                           "build-res <housing#>\n"
                           "improve <housing#>\n"
                           "trade <colour> <give> <take>\n"
                           "next\n"
                           "save <file>\n"
                           "help\n";

Game::Game(istream &input) : Controller(input), view{make_shared<View>()},
                             loaded{make_unique<LoadedDice>(view.get(), input)},
                             fair{make_unique<FairDice>()}, gameBoard{make_shared<Board>(view.get())}
{
}

Game::Game(const string &fileName, istream &input) : Game(input)
{
    read(fileName);
}

Game::Game(shared_ptr<BoardLayoutFactory> factory, istream &input) : Game(input)
{
    boardFactory = move(factory);
    int geeseIndex = boardFactory->createLayout(gameBoard.get());
    gameBoard->getGeese()->setPosition(geeseIndex);
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

bool Game::play()
{
    if(currentPlayerIndex==-1)
    {
        for (int i = 0; i < totalPlayers; i++)
            buildInitial(players[i].get());
        for (int i = totalPlayers - 1; i >= 0; i--)
            buildInitial(players[i].get());

        currentPlayerIndex=0;
    }

    gameBoard->print();

    for (;; currentPlayerIndex = (currentPlayerIndex + 1) % 4)
    {
        Player *currentPlayer = players[currentPlayerIndex].get();

        if (currentPlayer->getBuildingPoint() >= 10)
            return endGame();

        try
        {
            beginTurn(currentPlayer);
            duringTurn(currentPlayer);
        }
        catch (ios_base::failure &)
        {
            save();
            return false;
        }

        if (currentPlayer->getBuildingPoint() >= 10)
            return endGame();
    }
}

void Game::buildInitial(Player *player)
{
    int index;
    Color color = player->getColor();
    ostringstream message;
    message << "Builder " << toString(color) << ", where do you want to build a basement?";

    while (true)
    {
        view->printPrompt(message.str());
        input >> index;

        if (!(minVertexIndex <= index && index <= maxVertexIndex))
            view->printError(ErrorType::InvalidBuildOrImprove);
        else
        {
            Vertex *vertex = gameBoard->getVertex(index);
            if (vertex->trySetBuilding(BuildingType::Basement, player))
                return;
        }
    }
}

void Game::beginTurn(Player *player)
{
    ostringstream message;

    message << "Builder " << toString(player->getColor()) << "\'s turn." << endl;
    view->printMessage(message.str());

    int rollResult;
    try
    {
        rollResult = roll();
        if (rollResult == 7)
        {
            int newGeesePosition = moveGeese();
            stealFromOthers(player, newGeesePosition);
        }
        else
            obtainResources(rollResult);
    }
    catch (ios_base::failure &)
    { throw; }
}

int Game::roll()
{
    string cmd;
    shared_ptr<Dice> dice(nullptr);
    int rollResult;

    while (true)
    {
        view->printPrompt();

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

int Game::moveGeese()
{
    ostringstream message;
    int index;

    for (int i = 0; i < totalPlayers; i++)
        players[i]->loseResource();

    while (true)
    {
        view->printPrompt("Choose where to place the GEESE.");

        try
        { input >> index; }
        catch (ios_base::failure &)
        {
            if (input.eof()) throw;
            else
            {
                view->printError(ErrorType::InvalidInput);
                continue;
            }
        }

        if (gameBoard->getGeese()->tryMoveTo(index))
            break;
        else
            view->printError(ErrorType::InvalidInput);
    }

    return index;
}

void Game::stealFromOthers(Player *player, int geesePosition)
{
    ostringstream message;
    Tile *geeseTile = gameBoard->getTile(geesePosition);
    vector<Player *> playersToSteal = geeseTile->getResidenceOwners();

    if (playersToSteal.empty())
    {
        message << "Builder" << toString(player->getColor()) << " has no builders to steal from." << endl;
        view->printMessage(message.str());
        return;
    }

    message << "Builder " << toString(player->getColor()) << " can choose to steal from ";
    bool first = true;
    for (auto p : playersToSteal)
    {
        if (!first)
            message << ", ";
        else
            first = false;
        message << toString(p->getColor());
    }


    string colorStr;
    Color color;
    while (true)
    {
        view->printPrompt("Choose a builder to steal from.");

        try
        { input >> colorStr; }
        catch (ios_base::failure &)
        {
            if (input.eof()) throw;
            else
            {
                view->printError(ErrorType::InvalidInput);
                continue;
            }
        }

        try
        { color = toColor(colorStr); }
        catch (invalid_argument &)
        {
            view->printError(ErrorType::InvalidInput);
            continue;
        }

        break;
    }

    player->steal(players[static_cast<int>(color)].get());
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
                int numGained = players[i]->getResource(type) - resourcesSnapshot[i][type];
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

void Game::duringTurn(Player *player)
{
    string cmd;

    string fileName;

    int index;

    while (true)
    {
        view->printPrompt();

        try
        { input >> cmd; }
        catch (ios_base::failure &)
        { throw; }

        if (cmd == "board")
            gameBoard->print();
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
                if (input.eof()) throw;
                else
                {
                    view->printError(ErrorType::InvalidInput);
                    continue;
                }
            }

            if (cmd == "build-road" && (minEdgeIndex <= index && index <= maxEdgeIndex))
                gameBoard->getEdge(index)->buildRoad(player);
            else if (cmd == "build-res" && (minVertexIndex <= index && index <= maxVertexIndex))
                gameBoard->getVertex(index)->build(player);
            else if (cmd == "improve" && (minVertexIndex <= index && index <= maxVertexIndex))
                gameBoard->getVertex(index)->improve(player);
            else
                view->printError(ErrorType::InvalidBuildOrImprove);
        }
        else if (cmd == "trade")
            tradeWithOthers(player);
        else if (cmd == "next")
            return;
        else if (cmd == "save")
        {
            try
            { input >> fileName; }
            catch (ios_base::failure &)
            {
                if (input.eof()) throw;
                else
                {
                    view->printError(ErrorType::InvalidInput);
                    continue;
                }
            }

            save(fileName);
        }
        else if (cmd == "help")
            view->printMessage(helpMessage);
        else
            view->printError(ErrorType::InvalidCommand);
    }
}

void Game::tradeWithOthers(Player *player)
{
    string colorStr, takeStr, giveStr;
    Color otherColor;
    ResourceType take, give;

    try
    { input >> colorStr >> takeStr >> giveStr; }
    catch (ios_base::failure &)
    {
        if (input.eof()) throw;
        else
        {
            view->printError(ErrorType::InvalidInput);
            return;
        }
    }

    try
    {
        otherColor = toColor(colorStr);
        take = toResourceType(takeStr);
        give = toResourceType(giveStr);
    }
    catch (invalid_argument &)
    {
        view->printError(ErrorType::InvalidInput);
        return;
    }

    player->trade(players[static_cast<int>(otherColor)].get(), give, take);
}

bool Game::endGame()
{
    string response;

    while (true)
    {
        view->printPrompt("Would you like to play again?");

        try
        { input >> response; }
        catch (ios::failure &)
        {
            if (input.eof())
            {
                save();
                return false;
            }
            else
            {
                view->printError(ErrorType::InvalidInput);
                continue;
            }
        }

        if (response == "yes")
            return true;
        else if (response == "no")
            return false;
        else
            view->printError(ErrorType::InvalidInput);
    }
}

void Game::save(const string &fileName)
{
    ofstream file(fileName);

    file << currentPlayerIndex << endl;

    for (auto &p : players)
        file << p->toString() << endl;

    file << gameBoard->toString() << endl;

    file << gameBoard->getGeese()->getPosition();

    file.close();
}

void Game::read(const string &fileName)
{
    ifstream file(fileName);

    int curTurn;
    file >> curTurn;
    currentPlayerIndex = curTurn;

    for (int i = 0; i < totalPlayers; i++)
    {
        Player *player = players[i].get();

        string playerDataLine;
        getline(file, playerDataLine);

        istringstream playerData(playerDataLine);
        playerData.exceptions(ios_base::failbit);

        for (int j = 0; j < resourceTypeCount; j++)
        {
            auto type = static_cast<ResourceType>(j);
            int num;
            playerData >> num;
            players[i]->setResource(type, num);
        }

        char c, typeChar;
        int index;

        playerData >> c; // read in 'r'.
        while (true)
        {
            try
            { playerData >> index; }
            catch (ios::failure &)
            {
                playerData.clear();
                break;
            }

            gameBoard->getEdge(index)->setRoad(player);
            player->addRoad(index);
        }

        playerData >> c; // read in 'h'.
        while (!playerData.eof())
        {
            playerData >> index >> typeChar;
            BuildingType type = toBuildingType(type);

            gameBoard->getVertex(index)->setBuilding(type, player);
            player->addBuilding(index);
        }
    }

    boardFactory = make_shared<FileMode>(file);
    boardFactory->createLayout(gameBoard.get());

    int geesePosition;
    file >> geesePosition;
    gameBoard->getGeese()->setPosition(geesePosition);
}

