#ifndef BOARD_H
#define BOARD_H

#include "Tetrimino.hpp"

#define BOARD_WIDTH 10              // Board width in blocks
#define BOARD_HEIGHT 20             // Board height in blocks


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

    enum class Position : unsigned char {
        Free,   // free position of the board
        Filled  // filled position of the board
    };
    Position mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces

    void DeleteLine(const int& pY);
    void CheckLimits(const int& pX, const int& pY) const;
};

#endif // BOARD_H