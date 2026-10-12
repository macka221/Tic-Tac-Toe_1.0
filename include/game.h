#pragma once
#include <string>
#include "player.h"
#include "board.h"

using namespace std;

class Game {
  public:
    Game();
    ~Game();
    void newGame();
  protected:
    Player players[2];
    Board board;
  private:
    int currentPlayerIndex;
    void createPlayer();
    Player nextTurn();
    void displayStats();
    bool promptForReplay();
    bool promptForMove(int position);
    void promptForPlayerInfo();
}
