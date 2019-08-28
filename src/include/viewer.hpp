#ifndef VIEWER_H
#define VIEWER_H

#include "game.hpp"

class Viewer
{
public:
    static std::string Print(const Game* game);

private:
    static const char border;
    static const char filled;
    static const char piece;

    static bool IsPiece(const Game* game, const int& col, const int& row);

};

#endif