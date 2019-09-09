#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "state.hpp"
#include <unordered_map>
#include <functional>

State::State()
{
    // init the moves
    this->moves[Moves::Rotate] = std::bind(&State::Rotate, this);
    this->moves[Moves::Left] = std::bind(&State::MoveLeft, this);
    this->moves[Moves::Right] = std::bind(&State::MoveRight, this);
    this->moves[Moves::Down] = std::bind(&State::MoveDown, this);
    this->moves[Moves::Advance] = std::bind(&State::Advance, this);
    // init the pieces
    this->currentPiece = &this->pieces[0];
    this->pieces[1] = this->CreatePiece();
    this->nextPiece = &this->pieces[1];
    this->AddNewPiece();
}

const Tetrimino* State::GetCurrentPiece() const
{
    return this->currentPiece;
}

const Tetrimino* State::GetNextPiece() const
{
    return this->nextPiece;
}

const Position& State::GetCurrentPosition() const
{
    return this->currentPosition;
}

const Board& State::GetBoard() const
{
    return this->board;
}

int State::MoveDown()
{
    if (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col,
        this->currentPosition.row + 1))
    {
        this->currentPosition.row++;
    }
    return 0;
}

int State::MoveLeft()
{
    if (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col - 1,
        this->currentPosition.row))
    {
        this->currentPosition.col--;
    }
    return 0;
}

int State::MoveRight()
{
    if (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col + 1,
        this->currentPosition.row))
    {
        this->currentPosition.col++;
    }
    return 0;
}

int State::Rotate()
{
    this->currentPiece->Rotate();
    if (!this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col,
        this->currentPosition.row))
    {
        for (int ii = 1; ii < Tetrimino::NumberOfRotations; ii++)
        {
            this->currentPiece->Rotate();
        }
    }
    return 0;
}

int State::Advance()
{
    // move downwards as many times as it is possible
    while (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col,
        this->currentPosition.row + 1))
    {
        this->currentPosition.row++;
    }
    // add the piece at this location
    this->board.AddTetrimino(
        *this->currentPiece,
        this->currentPosition.col,
        this->currentPosition.row);
    // delete all possible lines above
    int linesDeleted = this->board.DeletePossibleLines();
    // check for game over or advance with new piece
    if (this->board.IsGameOver())
    {
        return -1;
    }
    else
    {
        this->AddNewPiece();
        return linesDeleted;
    }
}

void State::AddNewPiece()
{
    // the new piece
    std::swap(this->currentPiece, this->nextPiece);
    this->currentPosition = {
        0 - this->currentPiece->GetTopBlock(),
        (int)Board::Width/2 - this->currentPiece->GetLeftBlock() - 1
    };
    // Random next piece
    *this->nextPiece = this->CreatePiece();
}

Tetrimino State::CreatePiece() const
{
    int p = GetRand(0, Tetrimino::NumberOfTypes - 1);
    int rotation = GetRand(0, Tetrimino::NumberOfRotations - 1);
    return Tetrimino::Make(static_cast<Tetrimino::Type>(p), rotation);
}