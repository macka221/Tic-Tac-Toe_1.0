#pragma once

class Board {
  public:
    Board();
    ~Board();
    bool placePiece(int position, char piece);
    void getCurrentBoard();
    void resetBoard();
    void highlightWinningPositions(int position, char piece);
    enum gameState { CONTINUE, WIN, DRAW };
  private:
    bool checkWinningMove(int position, char piece);
    bool checkForADraw();
    char board[10];
};
