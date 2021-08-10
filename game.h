#ifndef CTOR_GAME_H
#define CTOR_GAME_H

#include <vector>
#include <memory>
#include <string>
#include <iostream>
#include "controller.h"
#include "view.h"
#include "board.h"
#include "boardLayoutFactory.h"
#include "dice.h"
#include "player.h"

const int totalPlayers = 4;
const int minWinningPoint = 10;

class Game : public Controller
{
    // Utilities
    std::unique_ptr<View> view;
    std::unique_ptr<BoardLayoutFactory> boardFactory;

    // Dices
    std::unique_ptr<Dice> loaded;
    std::unique_ptr<Dice> fair;

    // Game components
    static const int gameBeginningPlayerIndex = -1; // The index before building initial buildings.
    int currentPlayerIndex = gameBeginningPlayerIndex;
    std::unique_ptr<Board> gameBoard;
    std::vector<std::unique_ptr<Player>> players;

    void buildInitial(Player *player);

    void beginTurn(Player *player);
    int roll();
    int moveGeese(); // Returns the new position of the geese.
    void stealFromOthers(Player *player, int geesePosition);
    void obtainResources(int rollResult);

    bool duringTurn(Player *player); // true: we have a winner, false: continue playing.
    void tradeWithOthers(Player *player);

    bool endGame(); // true: play again, false: just exit.

    void save(const std::string &fileName = "backup.sv");
    void initPlayers(); // Add players in their default state to the empty player vector.
    void read(const std::string &fileName); // Read the entire class from file.

    explicit Game(std::istream &input); // Only initiate dices.
public:
    explicit Game(const std::string &fileName, std::istream &input = std::cin);
    explicit Game(std::unique_ptr<BoardLayoutFactory> factory, std::istream &input = std::cin);

    bool play(); // true: play again, false: just exit.
    ~Game() override = default;
};

#endif //CTOR_GAME_H
