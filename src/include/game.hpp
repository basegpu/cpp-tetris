#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "state.hpp"
#include "actions.hpp"
#include <thread>

// forward declaration
class Actions;

class Game
{
public:
    Game();
    virtual ~Game() {;}

    bool On() const;
    int GetScore() const;
    void MakeMove(const Moves& move);
    void PlaySequence(const Action& seq);
    void SelfPlay(const int& strategy);
    void Reset();
    void Print() const;

    friend class Viewer;

protected:
    const size_t nThreads;
    std::vector<std::thread> workers;
    State state;
    bool gameIsOn;
    int score;

    void UpdateScore(const int& scores);
    void PlayRandom();
    void PlayBest(const bool& includeNext);
    int MakeBestMoves(State& theState, const int& depth, const bool& parallel);
    std::vector<int> ValueActionsSequential(const State& state, const Actions& acts, const int& depth);
    std::vector<int> ValueActionsParallel(const State& state, const Actions& acts, const int& depth);
    int ValueSingleAction(State tempState, const Action& act, const int& depth);
    int MakeMove(const Moves& move, State& onState);
    int PlaySequence(const Action& action, State& onState);
    int Evaluate(const Board& board, const int& nLines);
};

#endif // GAME_H