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
    void Reset();
    void AddTetrimino(const Tetrimino& tetrimino, const int& pX, const int& pY);
    bool IsPossibleMove(const Tetrimino& tetrimino, const int& pX, const int& pY) const;
    int CountFilledBlocks() const;
    int GetHoles() const;
    int GetMaxLevel() const;
    int GetMinMaxLevel() const;
    bool IsFreeBlock(const int& pX, const int& pY) const;
    int DeletePossibleLines();
    bool IsGameOver() const;
    std::string Print() const;

protected:
    enum class Block : unsigned char
    {
        Free,   // free position of the board
        Filled  // filled position of the board
    };

    Block mBoard[BOARD_WIDTH][BOARD_HEIGHT]; // Board that contains the pieces
    int stats[3]; // nHoles, max level, min-max level

    void CalcStatistics();
    void DeleteLine(const int& pY);
    void LoopOverTetrimino(const Tetrimino& tetrimino, const int& pX, const int& pY, std::function<bool(const int&, const int&)> func) const;
    void LoopOverBoard(std::function<bool(const int&, const int&)> func, const int& bottomRow = BOARD_HEIGHT - 1, const int& topRow = 0) const;
    void CheckLimits(const int& pX, const int& pY) const;
    bool ValidLimits(const int& pX, const int& pY) const;
};

#endif // BOARD_H