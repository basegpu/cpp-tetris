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
    const Actions acts = Actions::GetPossibleActions(
        const_cast<Tetrimino&>(*this->state.GetCurrentPiece()),
        this->state.GetPosition());
    const int index = GetRand(0, acts.size() - 1);
    this->PlaySequence(acts.at(index));
}

void Game::PlayBest()
{
    const Actions acts = Actions::GetPossibleActions(
        const_cast<Tetrimino&>(*this->state.GetCurrentPiece()),
        this->state.GetPosition());
    std::vector<int> values;
    for (const Action& a : acts)
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
    this->score += this->PlaySequence(acts.at(bestAction), this->state);
}

void Game::Reset()
{
    this->gameIsOn = true;
    this->score = 0;
    this->state.Reset();
}

void Game::Print() const
{
    this->state.Print();
}

int Game::MakeMove(const Moves& move, State& onState)
{
    int out = onState.MakeMove(move);
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