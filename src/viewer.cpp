#include "viewer.hpp"
#include "game.hpp"
#include "tetrimino.hpp"
#include <sstream>
#include <string>

const std::string Viewer::border = "\033[31mI\033[0m";
const std::string Viewer::filled = "\033[34mO\033[0m";
const std::string Viewer::piece = "\033[32mX\033[0m";
const int Viewer::width = 20;

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
    out << "|                ";
    out << PieceForRow(game, 0) << "|" << std::endl;
    out << "|   SCORE: " << game->GetScore() << "  ";
    out << PieceForRow(game, 1) << "|" << std::endl;
    out << "|                ";
    out << PieceForRow(game, 2) << "|" << std::endl;
    out << "|   by sjp, 2019 ";
    out << PieceForRow(game, 3) << "|" << std::endl;
    for (int row = 4; row < Tetrimino::BlocksPerPiece; row++)
    {
        out << "|                ";
        out << PieceForRow(game, row) << "|" << std::endl;
    }
    out << LineWith(" ", "-");
    return out.str();
}

std::string Viewer::Board(const Game* game)
{
    std::string margin((width - Board::Width - 2), ' ');
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
    for (int ii = 0; ii < width - 2; ii++)
    {
        out << fill << fill;
    }
    out << fill << frame << std::endl;
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
