#include <utility>
#include "fairDice.h"
#include "loadedDice.h"
#include "player.h"
#include "game.h"
#include "boardFactory.h"

using namespace std;

Game::Game()
{
    random_device rd;

    loaded = make_unique<LoadedDice>(view.get());
    fair = make_unique<FairDice>(rd());
}

Game::Game(string &fileName) : Game()
{
    read(fileName);
}

Game::Game(shared_ptr<BoardFactory> factory) : Game()
{
    boardFactory = move(factory);
    gameBoard = boardFactory->createBoard(view.get());
    initPlayers();
}

void Game::initPlayers()
{
    for (int i = 0; i < TOTAL_PLAYERS; i++)
    {
        auto player = make_shared<Player>(view.get(), gameBoard.get(), static_cast<Color>(i));
        players.emplace_back(move(player));
    }
}


