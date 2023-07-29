#include "game.hpp"
#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "state.hpp"
#include "actions.hpp"
#include <vector>
#include <algorithm>
#include <thread>
#include <functional>

Game::Game() :
    nThreads(std::thread::hardware_concurrency()),
    workers(nThreads),
    gameIsOn(true),
    score(0)
{
    ;
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
    this->UpdateScore(out);
}

void Game::PlaySequence(const Action& seq)
{
    int out = this->PlaySequence(seq, this->state);
    this->UpdateScore(out);
}

void Game::SelfPlay(const int& strategy)
{
    if (strategy > 0)
    {
        this->PlayBest(strategy-1);
    }
    else
    {
        this->PlayRandom();
    }
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

void Game::UpdateScore(const int& scores)
{
    if (scores >= 0)
    {
        this->score += scores;
    }
    else
    {
        this->gameIsOn = false;
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

void Game::PlayBest(const bool& includeNext)
{
    int recursionDepth = includeNext ? 1 : 0;
    int out = this->MakeBestMoves(this->state, recursionDepth, false);
    this->UpdateScore(out);
}

int Game::MakeBestMoves(State& theState, const int& depth, const bool& parallel)
{
    const Actions acts = Actions::GetPossibleActions(
        const_cast<Tetrimino&>(*theState.GetCurrentPiece()),
        theState.GetPosition());
    std::vector<int> values(acts.size());
    if (parallel)
    {
        values = this->ValueActionsParallel(theState, acts, depth); 
    }
    else
    {
        values = this->ValueActionsSequential(theState, acts, depth);
    }
    int bestAction = std::max_element(values.begin(), values.end()) - values.begin();
    return this->PlaySequence(acts.at(bestAction), theState);
}

std::vector<int> Game::ValueActionsSequential(const State& theState, const Actions& acts, const int& depth)
{
    int n = acts.size();
    std::vector<int> values(n);
    for (int ii = 0; ii < n; ii++)
    {
        values.at(ii) = this->ValueSingleAction(theState, acts.at(ii), depth);
    }
    return values;
}

std::vector<int> Game::ValueActionsParallel(const State& theState, const Actions& acts, const int& depth)
{
    int n = acts.size();
    std::vector<int> values(n);
    const int slice = n/this->nThreads;
    for (int t = 0; t < this->nThreads; t++)
    {
        auto func = [this](
                const int th,
                const int bi,
                const int ei,
                const State& state,
                const Actions& acts,
                const int& depth,
                std::vector<int>* out)
            {
                // loop over all items
                for (int ii = bi; ii < ei; ii++)
                {
                    out->at(ii) = this->ValueSingleAction(state, acts.at(ii), depth);
                }
            };
        int i1 = t * slice;
        int i2 = (t+1) == this->nThreads ? n : (t+1)*slice;
        this->workers[t] = std::thread(func, t, i1, i2, theState, acts, depth, &values);
    }
    for (std::thread& x: this->workers)
    {
        x.join();
    }
    return values;
}

int Game::ValueSingleAction(State tempState, const Action& act, const int& depth)
{
    int nLines = this->PlaySequence(act, tempState);
    if (depth > 0)
    {
        nLines += this->MakeBestMoves(tempState, depth-1, false);
    }
    return (nLines < 0) ? -1e9 : this->Evaluate(tempState.GetBoard(), nLines);
}

int Game::MakeMove(const Moves& move, State& onState)
{
    return onState.MakeMove(move);
}

int Game::PlaySequence(const Action& seq, State& onState)
{
    int out, countLines = 0;
    for (const Moves& move : seq)
    {
        out = this->MakeMove(move, onState);
        if (out >= 0)
        {
            countLines += out;
        }
        else
        {
            countLines = out;
            break;
        }
    }
    return countLines;
}

int Game::Evaluate(const Board& board, const int& nLines)
{
    return 76 * nLines
        - 35 * board.GetHoles()
        - 51 * board.GetAggregateLevel()
        - 18 * board.GetBumpiness();
}