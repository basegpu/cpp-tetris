#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"

class Game
{
public:

    Game();
    ~Game();

    Tetrimino* piece = nullptr; // the piece that is falling down

    void AddNewPiece();


protected:

    Tetrimino* nextPiece = nullptr; // the next piece

    Tetrimino* CreatePiece() const;
    int GetRand(const int& pA, const int& pB) const;
};

#endif // GAME_H