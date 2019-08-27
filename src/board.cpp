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
    for (int x = pX, col = 0; x < pX + Tetrimino::BlocksPerPiece; x++, col++)
    {
        for (int y = pY, row = 0; y < pY + Tetrimino::BlocksPerPiece; y++, row++)
        {   
            // Store only the blocks of the piece that are not holes
            if (piece.GetShape(pRotation, row, col) != 0)
            {
                this->CheckLimits(x, y);
                this->mBoard[x][y] = Position::Filled;    
            }
        }
    }
}

bool Board::IsPossibleMove(const Tetrimino::Type& tetrimino, const int& pRotation, const int& pX, const int& pY)
{
    Tetrimino piece = Tetrimino::Make(tetrimino);
    // Checks collision with pieces already stored in the board or the board limits
    // This is just to check the 5x5 blocks of a piece with the appropriate area in the board
    for (int x = pX, col = 0; x < pX + Tetrimino::BlocksPerPiece; x++, col++)
    {
        for (int y = pY, row = 0; y < pY + Tetrimino::BlocksPerPiece; y++, row++)
        {   
            // only do checks if block is filled
            if (piece.GetShape(pRotation, row, col) != 0)
            {
                // Check if the piece is outside the limits of the board
                // or the piece have collisioned with a block already stored in the map
                if (!this->ValidLimits(x, y) || this->mBoard[x][y] == Position::Filled)
                {
                    return false;
                } 
            }
        }
    }
    // No collision
    return true;
}

int Board::CountFilledBlocks() const
{
    int count = 0;
    for (int ii = 0; ii < BOARD_WIDTH; ii++)
    {
        for (int jj = 0; jj < BOARD_HEIGHT; jj++)
        {
            count += (this->mBoard[ii][jj] == Position::Filled) ? 1 : 0;
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
            this->mBoard[ii][jj] = Position::Free;
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
            if (this->mBoard[ii][jj] != Position::Filled)
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
    if (!this->ValidLimits(pX, pY))
    {
        throw std::out_of_range("outside board");
    }
}

bool Board::ValidLimits(const int& pX, const int& pY) const
{
    if (pX >= BOARD_WIDTH || pY >= BOARD_HEIGHT)
    {
        return false;
    }
    return true;
}
