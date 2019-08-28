#ifndef GAME_H
#define GAME_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include <vector>

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

    void MakeMove(const Moves& move);
    void PlaySequence(const std::vector<Moves>& seq);

    friend class Viewer;

protected:
    typedef struct Position
    {
        int row;
        int col;
    } Position;

    Board* board = nullptr;
    // the piece that is falling down
    Tetrimino* piece = nullptr;
    Position currentPosition;
    // the next piece
    Tetrimino* nextPiece = nullptr;

    void AddNewPiece();

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