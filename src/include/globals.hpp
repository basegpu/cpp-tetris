#ifndef GLOBALS_H
#define GLOBALS_H

// tetrimino properties
#define TETRIMINO_WIDTH 4
#define TETRIMINO_NROTATIONS 4
#define TETRIMINO_NTYPES 7
#define TETRIMINO_HASHSIZE TETRIMINO_WIDTH*TETRIMINO_WIDTH+2

// board properties
#define BOARD_WIDTH 10              // Board width in blocks
#define BOARD_HEIGHT 20             // Board height in blocks

// viewer properties
#define VIEWER_WIDTH 20

// some compile checks
static_assert(BOARD_WIDTH >= TETRIMINO_WIDTH,
    "Board width must be at least the number of blocks per TETRIMINO");
static_assert(BOARD_HEIGHT >= TETRIMINO_WIDTH,
    "Board height must be at least the number of blocks per TETRIMINO");
static_assert(VIEWER_WIDTH >= BOARD_WIDTH+2,
    "Viewer width must be at least the board width plus border (+2)");


#endif