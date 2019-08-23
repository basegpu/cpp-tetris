#ifndef BOARD_H
#define BOARD_H

#include "Tetrimino.hpp"

//#define BOARD_LINE_WIDTH 6          // Width of each of the two lines that delimit the board
//#define BOARD_POSITION 320          // Center position of the board from the left of the screen
//#define BLOCK_SIZE 16               // Width and Height of each block of a piece
#define BOARD_WIDTH 10              // Board width in blocks
#define BOARD_HEIGHT 20             // Board height in blocks
//#define MIN_VERTICAL_MARGIN 20      // Minimum vertical margin for the board limit
//#define MIN_HORIZONTAL_MARGIN 20    // Minimum horizontal margin for the board limit


class Board
{
public:

    Board();
    void AddTetrimino(const Tetrimino::Type& tetrimino, const int& pRotation, const int& pX, const int& pY);
    bool IsFreeBlock(const int& pX, const int& pY);
    bool IsGameOver();

private:

    enum class Position : unsigned char {
        Free,   // free position of the board
        Filled  // filled position of the board
    };
    Position mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces

    void Initialize();
    void CheckLimits(const int& pX, const int& pY);
};

#endif // BOARD_H