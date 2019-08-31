#include "viewer.hpp"
#include "globals.hpp"
#include "game.hpp"
#include "tetrimino.hpp"
#include <sstream>
#include <string>
#include <iomanip>

const std::string Viewer::border = "\033[31mI\033[0m";
const std::string Viewer::filled = "\033[34mO\033[0m";
const std::string Viewer::piece = "\033[32mX\033[0m";

std::string Viewer::Print(const Game* game)
{
    std::ostringstream out;
    out << Header(game);
    out << std::endl << std::endl;
    out << Board(game);
    return out.str();
}

std::string Viewer::Header(const Game* game)
{
    std::ostringstream out;
    out << LineWith(" ", "-");
    out << Viewer::LineWithPiece(game, 0, "              ");
    char score[15];
    sprintf(score, "  SCORE:%6i", game->GetScore());
    out << Viewer::LineWithPiece(game, 1, std::string(score));
    out << Viewer::LineWithPiece(game, 2, "              ");
    out << Viewer::LineWithPiece(game, 3, "  by sjp, 2019");
    for (int row = 4; row < Tetrimino::BlocksPerPiece; row++)
    {
        out << Viewer::LineWithPiece(game, row, "              ");
    }
    out << LineWith(" ", "-");
    return out.str();
}

std::string Viewer::Board(const Game* game)
{
    std::string margin((VIEWER_WIDTH - Board::Width - 2), ' ');
    std::ostringstream out;
    for (int jj = 0; jj < Board::Height; jj++)
    {
        out << margin << border;
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
    out << margin << border;
    for (int ii = 0; ii < Board::Width + 1; ii++)
        out << " " << border;
    out << std::endl;
    return out.str();
}

std::string Viewer::LineWith(const std::string& frame, const std::string& fill)
{
    std::ostringstream out;
    out << frame;
    out << std::setfill(fill.c_str()[0]) << std::setw(2*(VIEWER_WIDTH-1)) << frame;
    out << std::endl;
    return out.str();
}

std::string Viewer::LineWithPiece(const Game* game, const int&row, const std::string& prefix)
{
    const int pieceMargin = 4;
    const int gab = 2*VIEWER_WIDTH - 1 - pieceMargin - 2*Tetrimino::BlocksPerPiece - prefix.size();
    std::ostringstream out;
    out << "|" << prefix;
    out << std::setfill(' ') << std::setw(gab-1) << " "; // -1 because string length of formatted piece
    out << PieceForRow(game, row);
    out << std::setfill(' ') << std::setw(pieceMargin) << "|" << std::endl;
    return out.str();
}

std::string Viewer::PieceForRow(const Game* game, const int& row)
{
    std::ostringstream out;
    if (row < Tetrimino::BlocksPerPiece)
    {
        for (int ii = 0; ii < Tetrimino::BlocksPerPiece; ii++)
        {
            out << " ";
            if (game->nextPiece->GetShape(row, ii) != 0)
            {
                out << filled;
            }
            else
            {
                out << " ";
            }
        }
    }
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
