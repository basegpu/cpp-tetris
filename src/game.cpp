#include "game.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "state.hpp"
#include "actions.hpp"
#include <vector>
#include <algorithm>

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
    int out = this->MakeMove(move, this->state);
    if (this->gameIsOn)
    {
        this->score += out;
    }
}

void Game::PlaySequence(const Action& seq)
{
    this->score += this->PlaySequence(seq, this->state);
}

void Game::SelfPlay(const bool& withStrategy)
{
    if (withStrategy)
    {
        this->PlayBest();
    }
    else
    {
        this->PlayRandom();
    }
}

void Game::PlayRandom()
{
    const Actions acts = this->GetPossibleActions();
    const int index = GetRand(0, acts.size() - 1);
    this->PlaySequence(acts.at(index));
}

void Game::PlayBest()
{
    std::vector<int> values;
    for (const Action& a : this->GetPossibleActions())
    {
        State tempState = this->state;
        int nLines = this->PlaySequence(a, tempState);
        // evaluation
        int v = 76 * nLines
                - 35 * tempState.GetBoard().GetHoles()
                - 51 * tempState.GetBoard().GetAggregateLevel()
                - 18 * tempState.GetBoard().GetBumpiness();
        values.push_back(v);
    }
    int bestAction = std::max_element(values.begin(), values.end()) - values.begin();
    this->score += this->PlaySequence(this->GetPossibleActions().at(bestAction), this->state);
}

int Game::MakeMove(const Moves& move, State& onState)
{
    int out = onState.moves.at(move)();
    if (out < 0)
    {
        this->gameIsOn = false;
    }
    return out;
}

int Game::PlaySequence(const Action& seq, State& onState)
{
    int out, countLines = 0;
    for (const Moves& move : seq)
    {
        out = this->MakeMove(move, onState);
        if (this->gameIsOn)
        {
            countLines += out;
        }
        else
        {
            break;
        }
    }
    return countLines;
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