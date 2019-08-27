#include "board.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include <functional>
#include <stdexcept>
#include <iostream>

const size_t Board::Width = BOARD_WIDTH;

const size_t Board::Height = BOARD_HEIGHT;

Board::Board()
{
    this->Reset();
}

void Board::AddTetrimino(
    const Tetrimino* tetrimino,
    const int& pRotation,
    const int& pX,
    const int& pY)
{
    auto func = [&, this](const int& x, const int& y) -> bool {
        // Check if within the boundaries
        this->CheckLimits(x, y);
        // if ok, then set the position as filled
        this->mBoard[x][y] = Position::Filled;
        // and return true to continue with looping
        return true;
    };
    this->LoopOverTetrimino(tetrimino, pRotation, pX, pY, func);
}

bool Board::IsPossibleMove(
    const Tetrimino* tetrimino,
    const int& pRotation,
    const int& pX,
    const int& pY)
{
    bool isPossible = true;
    auto func = [this, &isPossible](const int& x, const int& y) mutable -> bool {
        // Check if the piece is outside the limits of the board
        // or the piece have collisioned with a block already stored in the map
        if (!this->ValidLimits(x, y) || this->mBoard[x][y] == Position::Filled)
        {
            isPossible = false;
            // stop looping
            return false;
        }
        // continue with looping
        return true;
    };
    this->LoopOverTetrimino(tetrimino, pRotation, pX, pY, func);
    return isPossible;
}

int Board::CountFilledBlocks()
{
    int count = 0;
    auto func = [this, &count](const int& ii, const int& jj) -> bool {
        count += (this->mBoard[ii][jj] == Position::Filled) ? 1 : 0;
        return true;
    };
    this->LoopOverBoard(func);
    return count;
}

void Board::Reset()
{
    auto func = [&, this](const int& ii, const int& jj) -> bool {
        this->mBoard[ii][jj] = Position::Free;
        return true;
    };
    this->LoopOverBoard(func);
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
    int counter = 0;
    auto func = [this, &counter](const int& ii, const int& jj) -> bool {
        // count filled blocks
        if (this->mBoard[ii][jj] == Position::Filled)
        {
            counter++;
        }
        // in case of last column
        if (ii == BOARD_WIDTH - 1)
        {
            // check if the line is completely filled
            if (counter == BOARD_WIDTH)
            {
                // then delete this line
                this->DeleteLine(jj);
            }
            // reset counter
            counter = 0;
        }
        // keep on going
        return true;
    };
    this->LoopOverBoard(func);
}

bool Board::IsGameOver() const
{
    // If the first line has blocks, then, game over
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
    auto func = [&, this](const int& ii, const int& jj) -> bool {
        this->mBoard[ii][jj] = this->mBoard[ii][jj-1];
        return true;
    };
    this->LoopOverBoard(func, pY, 1);
}

void Board::LoopOverTetrimino(
    const Tetrimino* tetrimino,
    const int& pRotation,
    const int& pX,
    const int& pY,
    std::function<bool(const int&, const int&)> func)
{
    // Store each block of the piece into the board
    for (int x = pX, col = 0; x < pX + Tetrimino::BlocksPerPiece; x++, col++)
    {
        for (int y = pY, row = 0; y < pY + Tetrimino::BlocksPerPiece; y++, row++)
        {   
            // Store only the blocks of the piece that are not holes
            if (tetrimino->GetShape(pRotation, row, col) != 0)
            {
                if(!func(x, y))
                {
                    return;
                }  
            }
        }
    }
}

void Board::LoopOverBoard(
    std::function<bool(const int&, const int&)> func,
    const int& bottomRow,
    const int& topRow)
{
    // from bottom to top
    for (int jj = bottomRow; jj >= topRow; jj--)
    {
        for (int ii = 0; ii < BOARD_WIDTH; ii++)
        {
            if(!func(ii, jj))
            {
                return;
            }
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
