#include "Board.hpp"
#include "Tetrimino.hpp"


Board::Board(const int& pScreenHeight) :
	mScreenHeight(pScreenHeight)
{
	this->Initialize();
}

bool Board::IsFreeBlock(const int& pX, const int& pY)
{
    if (this->mBoard[pX][pY] == Position::Free)
    {
   		return true;
   	}
   	else
   	{
   		return false;
   	}
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