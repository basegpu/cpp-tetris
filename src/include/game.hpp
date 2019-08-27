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


protected:

	typedef struct Position
	{
		int row;
		int col;
	} Position;

	Board* board = nullptr;
	// the piece that is falling down
	Tetrimino* piece = nullptr;
	Position currentPosition;
	// the next piece
    Tetrimino* nextPiece = nullptr;

    void AddNewPiece();


private:

    Tetrimino* CreatePiece() const;
    int GetRand(const int& pA, const int& pB) const;
};

#endif // GAME_H