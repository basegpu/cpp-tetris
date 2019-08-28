#ifndef VIEWER_H
#define VIEWER_H

#include "game.hpp"

class Viewer
{
public:
    static std::string Print(const Game* game);

private:
    static const std::string border;
    static const std::string filled;
    static const std::string piece;

    static bool IsPiece(const Game* game, const int& col, const int& row);

};

#endif