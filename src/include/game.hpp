#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include "actions.hpp"
#include <map>

// forward declaration
class Actions;

class Game
{
public:
    Game();
    Game(const bool& random);
    virtual ~Game() {;}

    bool On() const;
    int GetScore() const;
    void MakeMove(const Moves& move);
    void PlaySequence(const Action& seq);
    void PlayRandom();

    friend class Viewer;

protected:
    Board board;
    // the piece that is falling down
    Tetrimino piece;
    Position currentPosition;
    // the next piece
    Tetrimino nextPiece;
    // registry of all possible actions for given tetrimino
    std::map<size_t, Actions> actionsRegistry;

    void AddNewPiece();
    const Actions& GetPossibleActions();

private:
    bool gameIsOn;
    int score;

    void MoveDown();
    void MoveLeft();
    void MoveRight();
    void Rotate();
    void Advance();

    Tetrimino CreatePiece() const;
    int GetRand(const int& pA, const int& pB) const;
};

#endif // GAME_H