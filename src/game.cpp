#include "game.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "actions.hpp"
#include <ctime>
#include <cstdlib>
#include <sstream>
#include <algorithm>

Game::Game() :
    Game(true)
{
    ;
}

Game::Game(const bool& random) :
    gameIsOn(true),
    score(0)
{
    // eventually seed random numbers
    if (random)
    {
        srand((unsigned int) time(NULL));
    }
    else
    {
        srand(1);
    }
    // Next piece
    this->currentPiece = &this->pieces[0];
    this->pieces[1] = this->CreatePiece();
    this->nextPiece = &this->pieces[1];
    this->AddNewPiece();
}

bool Game::On() const
{
    return this->gameIsOn;
}

int Game::GetScore() const
{
    return this->score;
}

void Game::MakeMove(const Moves& move)
{
    switch (move)
    {
        case Moves::Advance: this->Advance();   break;
        case Moves::Rotate:  this->Rotate();    break;
        case Moves::Down:    this->MoveDown();  break;
        case Moves::Left:    this->MoveLeft();  break;
        case Moves::Right:   this->MoveRight(); break;
        default: break;
    }
}

void Game::PlaySequence(const Action& seq)
{
    for (const Moves& move : seq)
    {
        this->MakeMove(move);
    }
}

void Game::PlayRandom()
{
    const Actions acts = this->GetPossibleActions();
    const int index = this->GetRand(0, acts.size() - 1);
    for (const Moves& move : acts.at(index))
    {
        this->MakeMove(move);
    }
}

void Game::MoveDown()
{
    if (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col,
        this->currentPosition.row + 1))
    {
        this->currentPosition.row++;
    }
}

void Game::MoveLeft()
{
    if (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col - 1,
        this->currentPosition.row))
    {
        this->currentPosition.col--;
    }
}

void Game::MoveRight()
{
    if (this->board.IsPossibleMove(
        *this->currentPiece,
        this->currentPosition.col + 1,
        this->currentPosition.row))
    {
        this->currentPosition.col++;
    }
}

void Game::Rotate()
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
}

void Game::Advance()
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
    this->score += this->board.DeletePossibleLines();
    // check for game over or advance with new piece
    if (!this->board.IsGameOver())
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
    // the new piece
    std::swap(this->currentPiece, this->nextPiece);
    this->currentPosition = {
        0 - this->currentPiece->GetTopBlock(),
        (int)Board::Width/2 - this->currentPiece->GetLeftBlock() - 1
    };
    // Random next piece
    *this->nextPiece = this->CreatePiece();
}

const Actions& Game::GetPossibleActions()
{
    size_t hash = this->currentPiece->GetHash();
    if (this->actionsRegistry.count(hash) == 0)
    { 
        // we have to generate all possible actions
        // and add them to hash table
        this->actionsRegistry[hash] = Actions::CreateFor(*this->currentPiece, this->currentPosition);
    }
    return this->actionsRegistry.at(hash);
}

Tetrimino Game::CreatePiece() const
{
    int p = this->GetRand(0, Tetrimino::NumberOfTypes - 1);
    int rotation = this->GetRand(0, Tetrimino::NumberOfRotations - 1);
    return Tetrimino::Make(static_cast<Tetrimino::Type>(p), rotation);
}

int Game::GetRand(const int& pA, const int& pB) const
{
    return std::rand() % (pB - pA + 1) + pA;
}