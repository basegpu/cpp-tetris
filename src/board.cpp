#include "Board.hpp"
#include "Tetrimino.hpp"


Board::Board(const int& pScreenHeight) :
	mScreenHeight(pScreenHeight)
{
	this->Initialize();
}

void Board::Initialize()
{
	for (int ii = 0; ii < BOARD_WIDTH; ii++)
	{
        for (int jj = 0; jj < BOARD_HEIGHT; jj++)
        {
            mBoard[ii][jj] = Position::Free;
        }
	}
}