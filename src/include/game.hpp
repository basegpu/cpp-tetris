#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include <vector>
#include <map>

// forward declaration
class Actions;

class Game
{
public:
    Game();
    Game(const bool& random);
    ~Game();

    bool On() const;
    int GetScore() const;

    enum class Moves : int {
        Advance,
        Rotate,
        Down,
        Left,
        Right
    };
    typedef struct Position
    {
        int row;
        int col;
    } Position;
    typedef std::vector<Moves> Action;

    void MakeMove(const Moves& move);
    void PlaySequence(const Action& seq);
    void PlayRandom();

    friend class Viewer;

protected:
    Board* board = nullptr;
    // the piece that is falling down
    Tetrimino* piece = nullptr;
    Position currentPosition;
    // the next piece
    Tetrimino* nextPiece = nullptr;
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

    Tetrimino* CreatePiece() const;
    int GetRand(const int& pA, const int& pB) const;
};

#endif // GAME_H