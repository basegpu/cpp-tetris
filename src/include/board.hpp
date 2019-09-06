#ifndef BOARD_H
#define BOARD_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include <functional>
#include <string>

class Board
{
public:
    static const size_t Width;
    static const size_t Height;

    Board();
    void AddTetrimino(const Tetrimino* tetrimino, const int& pX, const int& pY);
    bool IsPossibleMove(const Tetrimino* tetrimino, const int& pX, const int& pY);
    int CountFilledBlocks();
    int CountHoles();
    void Reset();
    bool IsFreeBlock(const int& pX, const int& pY) const;
    int DeletePossibleLines();
    bool IsGameOver() const;
    std::string Print();

protected:
    enum class Block : unsigned char
    {
        Free,   // free position of the board
        Filled  // filled position of the board
    };

    Block mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces

    void DeleteLine(const int& pY);
    void LoopOverTetrimino(const Tetrimino* tetrimino, const int& pX, const int& pY, std::function<bool(const int&, const int&)> func);
    void LoopOverBoard(std::function<bool(const int&, const int&)> func, const int& bottomRow = BOARD_HEIGHT - 1, const int& topRow = 0);
    void CheckLimits(const int& pX, const int& pY) const;
    bool ValidLimits(const int& pX, const int& pY) const;
};

#endif // BOARD_H