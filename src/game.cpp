#include "game.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "state.hpp"
#include "actions.hpp"

Game::Game() :
    gameIsOn(true),
    score(0)
{
    
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
    int out = this->state.moves.at(move)();
    if (out >= 0)
    {
        this->score += out;
    }
    else
    {
        this->gameIsOn = false;
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
    const int index = GetRand(0, acts.size() - 1);
    for (const Moves& move : acts.at(index))
    {
        this->MakeMove(move);
    }
}

const Actions& Game::GetPossibleActions()
{
    const Tetrimino* piece = this->state.GetCurrentPiece();
    size_t hash = piece->GetHash();
    if (this->actionsRegistry.count(hash) == 0)
    { 
        // we have to generate all possible actions
        // and add them to hash table
        this->actionsRegistry[hash] = Actions::CreateFor(
            const_cast<Tetrimino&>(*piece),
            this->state.GetPosition());
    }
    return this->actionsRegistry.at(hash);
}