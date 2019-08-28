#include "viewer.hpp"
#include "game.hpp"
#include "tetrimino.hpp"
#include <sstream>

const char Viewer::border = 'I';
const char Viewer::filled = 'O';
const char Viewer::piece = 'X';

std::string Viewer::Print(const Game* game)
{
    std::ostringstream out;
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
