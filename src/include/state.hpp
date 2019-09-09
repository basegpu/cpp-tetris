#ifndef STATE_H
#define STATE_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include <unordered_map>
#include <functional>

class State
{
public:
    State();
    State(const State& other);
    virtual ~State() {;}

    const Tetrimino* GetCurrentPiece() const;
    const Tetrimino* GetNextPiece() const;
    const Position& GetPosition()const;
    const Board& GetBoard() const;

    // map from moves to functions
    std::unordered_map<Moves, std::function<int()>> moves;

    friend class Viewer;

protected:
    Board board;
    // the position of current piece
    Position position;
    // two pieces (one falling down and the next one)
    Tetrimino pieces[2];
    // pointer of current piece
    Tetrimino* currentPiece;
    // pointer of next piece
    Tetrimino* nextPiece;

    int MoveDown();
    int MoveLeft();
    int MoveRight();
    int Rotate();
    int Advance();

    void AddNewPiece();
    Tetrimino CreatePiece() const;
};

#endif // STATE_H