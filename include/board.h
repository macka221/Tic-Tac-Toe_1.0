#pragma once

class Board {
  public:
    Board();
    ~Board();
    bool placePiece(int position, char piece);
    void getCurrentBoard();
    void resetBoard();
    void highlightWinningPositions(int position, char piece);
    enum gameState { WIN, DRAW, CONTINUE } = CONTINUE;
  private:
    bool checkWinningMove(int position, char piece);
    bool checkForADraw();
    char board[10];
}
