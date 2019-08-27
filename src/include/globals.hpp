#ifndef GLOBALS_H
#define GLOBALS_H

#define TETRIMINO_WIDTH 4
#define TETRIMINO_NROTATIONS 4
#define TETRIMINO_NTYPES 7

#define BOARD_WIDTH 10              // Board width in blocks
#define BOARD_HEIGHT 20             // Board height in blocks

// typedefs

enum class Position : unsigned char
{
    Free,   // free position of the board
    Filled  // filled position of the board
};

#endif