#include "viewer.hpp"
#include "game.hpp"
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
                out << filled;
            else
                out << " ";
        }
        out << " " << border << std::endl;
    }
    out << border;
    for (int ii = 0; ii < Board::Width + 1; ii++)
        out << " " << border;
    return out.str();
}