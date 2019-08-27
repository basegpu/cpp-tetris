#include "board.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include <stdexcept>


Board::Board()
{
    this->Reset();
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

int Board::CountFilledBlocks() const
{
    int count = 0;
    for (int ii = 0; ii < BOARD_WIDTH; ii++)
    {
        for (int jj = 0; jj < BOARD_HEIGHT; jj++)
        {
            count += (mBoard[ii][jj] == Position::Filled) ? 1 : 0;
        }
    }
    return count;
}

void Board::Reset()
{
    for (int ii = 0; ii < BOARD_WIDTH; ii++)
    {
        for (int jj = 0; jj < BOARD_HEIGHT; jj++)
        {
            mBoard[ii][jj] = Position::Free;
        }
    }
}

bool Board::IsFreeBlock(const int& pX, const int& pY) const
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

void Board::DeletePossibleLines()
{
    // loop over all lines from the bottom
    for (int jj = 0; jj < BOARD_HEIGHT; jj++)
    {
        // check if all blocks are filled
        int ii = 0;
        while (ii < BOARD_WIDTH)
        {
            if (mBoard[ii][jj] != Position::Filled)
            {
                break;
            }
            ii++;
        }
        // then remove that line
        if (ii == BOARD_WIDTH)
        {
            this->DeleteLine(jj);
        }
    }
}

bool Board::IsGameOver() const
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

void Board::DeleteLine(const int& pY)
{
    this->CheckLimits(0, pY);
    // Moves all the upper lines one row down
    for (int jj = pY; jj > 0; jj--)
    {
        for (int ii = 0; ii < BOARD_WIDTH; ii++)
        {
            this->mBoard[ii][jj] = this->mBoard[ii][jj-1];
        }
    }   
}

void Board::CheckLimits(const int& pX, const int& pY) const
{
    if (pX >= BOARD_WIDTH || pY >= BOARD_HEIGHT)
    {
        throw std::out_of_range("outside board");
    }
}
