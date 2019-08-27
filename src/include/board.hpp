#ifndef BOARD_H
#define BOARD_H

#include "globals.hpp"
#include "tetrimino.hpp"

class Board
{
public:

    Board();
    void AddTetrimino(const Tetrimino::Type& tetrimino, const int& pRotation, const int& pX, const int& pY);
    int CountFilledBlocks() const;
    void Reset();
    bool IsFreeBlock(const int& pX, const int& pY) const;
    void DeletePossibleLines();
    bool IsGameOver() const;

protected:

    Position mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces

    void DeleteLine(const int& pY);
    void CheckLimits(const int& pX, const int& pY) const;
};

#endif // BOARD_H