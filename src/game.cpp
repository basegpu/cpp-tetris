#include "game.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include <ctime>
#include <cstdlib>

Game::Game() :
    board(new Board())
{
    // Init random numbers
    srand((unsigned int) time(NULL));
    // First piece
    this->piece = this->CreatePiece();
    // Next piece
    this->nextPiece = this->CreatePiece();
}

Game::~Game()
{
    delete this->piece;
    delete this->nextPiece;
}

void Game::AddNewPiece()
{
    // delete old piece
    delete this->piece;
    // The new piece
    this->piece = this->nextPiece;
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