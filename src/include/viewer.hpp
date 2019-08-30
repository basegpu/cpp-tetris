#ifndef VIEWER_H
#define VIEWER_H

#include "game.hpp"
#include <string>

class Viewer
{
public:
    static std::string Print(const Game* game);

private:
    static const std::string border;
    static const std::string filled;
    static const std::string piece;
    static const int width;

    static std::string Header(const Game* game);
    static std::string Board(const Game* game);
    static std::string LineWith(const std::string& frame, const std::string& fill);
    static std::string LineWithPiece(const Game* game, const int&row, const std::string& prefix);
    static std::string PieceForRow(const Game* game, const int& row);
    static bool IsPiece(const Game* game, const int& col, const int& row);

};

#endif