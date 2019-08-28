#include "viewer.hpp"
#include "game.hpp"
#include "tetrimino.hpp"
#include <sstream>

const std::string Viewer::border = "\033[31mI\033[0m";
const std::string Viewer::filled = "\033[34mO\033[0m";
const std::string Viewer::piece = "\033[32mX\033[0m";

std::string Viewer::Print(const Game* game)
{
    std::ostringstream out;
    out << std::endl << "SCORE: " << game->GetScore() << std::endl << std::endl;
    for (int jj = 0; jj < Board::Height; jj++)
    {
        out << border;
        for (int ii = 0; ii < Board::Width; ii++)
        {
            out << " ";
            if (!game->board->IsFreeBlock(ii, jj))
            {
                out << filled;
            }
            else if (Viewer::IsPiece(game, ii, jj))
            {
                out << piece;
            }
            else
            {
                out << " ";
            }
        }
        out << " " << border << std::endl;
    }
    out << border;
    for (int ii = 0; ii < Board::Width + 1; ii++)
        out << " " << border;
    out << std::endl;
    return out.str();
}

bool Viewer::IsPiece(const Game* game, const int& col, const int& row)
{
    const int iLocal = col - game->currentPosition.col;
    const int jLocal = row - game->currentPosition.row;
    if (iLocal >= 0 &&
        iLocal < Tetrimino::BlocksPerPiece &&
        jLocal >= 0 &&
        jLocal < Tetrimino::BlocksPerPiece)
    {
        if (game->piece->GetShape(jLocal, iLocal) != 0)
        {
            return true;
        }
    }
    return false;
}
