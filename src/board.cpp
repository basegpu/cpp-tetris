#include "Board.hpp"
#include "Tetrimino.hpp"
#include <stdexcept>


Board::Board()
{
    this->Initialize();
}

void Board::AddTetrimino(const Tetrimino::Type& tetrimino, const int& pRotation, const int& pX, const int& pY)
{
    Tetrimino piece = Tetrimino::Make(tetrimino);
    // Store each block of the piece into the board
    for (int i1 = pX, i2 = 0; i1 < pX + Tetrimino::BlocksPerPiece; i1++, i2++)
    {
        for (int j1 = pY, j2 = 0; j1 < pY + Tetrimino::BlocksPerPiece; j1++, j2++)
        {   
            // Store only the blocks of the piece that are not holes
            if (piece.GetShape(pRotation, j2, i2) != 0)
            {
                this->CheckLimits(i1, j1);
                this->mBoard[i1][j1] = Position::Filled;    
            }
        }
    }
}

bool Board::IsFreeBlock(const int& pX, const int& pY)
{
    this->CheckLimits(pX, pY);
    if (this->mBoard[pX][pY] == Position::Free)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Board::IsGameOver()
{
    //If the first line has blocks, then, game over
    for (int ii = 0; ii < BOARD_WIDTH; ii++)
    {
        if (this->mBoard[ii][0] == Position::Filled)
        {
            return true;
        }
    }
    return false;
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

void Board::CheckLimits(const int& pX, const int& pY)
{
    if (pX >= BOARD_WIDTH || pY >= BOARD_HEIGHT)
    {
        throw std::out_of_range("outside board");
    }
}
