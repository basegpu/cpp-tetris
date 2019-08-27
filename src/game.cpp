#include "game.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include <ctime>
#include <cstdlib>

Game::Game() :
    board(new Board()),
    gameIsOn(true)
{
    // Init random numbers
    srand((unsigned int) time(NULL));
    // Next piece
    this->nextPiece = this->CreatePiece();
    this->AddNewPiece();
}

Game::~Game()
{
    delete this->nextPiece;
    delete this->piece;
    delete this->board;
}

void Game::Print(std::ostream& out) const
{
    this->board->Print(out);
}

bool Game::On() const
{
    return this->gameIsOn;
}

void Game::MoveDown()
{
    if (this->board->IsPossibleMove(
        this->piece,
        this->currentPosition.col,
        this->currentPosition.row + 1))
    {
        this->currentPosition.row++;
    }
}

void Game::MoveLeft()
{
    if (this->board->IsPossibleMove(
        this->piece,
        this->currentPosition.col - 1,
        this->currentPosition.row))
    {
        this->currentPosition.col--;
    }
}

void Game::MoveRight()
{
    if (this->board->IsPossibleMove(
        this->piece,
        this->currentPosition.col + 1,
        this->currentPosition.row))
    {
        this->currentPosition.col++;
    }
}

void Game::Rotate()
{
    this->piece->Rotate();
    if (!this->board->IsPossibleMove(
        this->piece,
        this->currentPosition.col,
        this->currentPosition.row))
    {
        for (int ii = 1; ii < Tetrimino::NumberOfRotations; ii++)
        {
            this->piece->Rotate();
        }
    }
}

void Game::Advance()
{
    // move downwards as many times as it is possible
    while (this->board->IsPossibleMove(
        this->piece,
        this->currentPosition.col,
        this->currentPosition.row + 1))
    {
        this->currentPosition.row++;
    }
    // add the piece at this location
    this->board->AddTetrimino(
        this->piece,
        this->currentPosition.col,
        this->currentPosition.row);
    // delete all possible lines above
    this->board->DeletePossibleLines();
    // check for game over or advance with new piece
    if (!this->board->IsGameOver())
    {
        this->AddNewPiece();
    }
    else
    {
        this->gameIsOn = false;
    }
}

void Game::AddNewPiece()
{
    // delete old piece
    if (this->piece) delete this->piece;
    // The new piece
    this->piece = this->nextPiece;
    this->currentPosition = {
        0 - this->piece->GetTopBlock(),
        (int)Board::Width/2 - this->piece->GetLeftBlock()
    };
    // Random next piece
    this->nextPiece = this->CreatePiece();
}

Tetrimino* Game::CreatePiece() const
{
    int piece = this->GetRand(0, Tetrimino::NumberOfTypes - 1);
    int rotation = this->GetRand(0, Tetrimino::NumberOfRotations - 1);
    return Tetrimino::Make(static_cast<Tetrimino::Type>(piece), rotation);
}

int Game::GetRand(const int& pA, const int& pB) const
{
    return std::rand() % (pB - pA + 1) + pA;
}