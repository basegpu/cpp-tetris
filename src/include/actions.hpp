#ifndef ACTION_H
#define ACTION_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include <vector>
#include <map>

class Actions : public std::vector<Action>
{
public:
    static std::map<size_t, Actions> Registry;
    static const Actions& GetPossibleActions(Tetrimino& piece, const Position& position);

protected:
    static const Actions CreateFor(Tetrimino& tetrimino, const Position& position);
};

#endif