#ifndef ACTION_H
#define ACTION_H

#include "globals.hpp"
#include "game.hpp"
#include "tetrimino.hpp"
#include "board.hpp"
#include <vector>

typedef std::vector<Game::Moves> Action;

class Actions : public std::vector<const Action>
{
public:
    static Actions CreateFor(Tetrimino* tetrimino, const Game::Position& position)
    {
        TETRIS_MESSAGE("creating new action for tetrimino <" << tetrimino->GetHash() << ">");
        // check th possible enumber of rotations
        int nRot;
        switch (tetrimino->GetSymmetry())
        {
            case (Tetrimino::Symmetry::None): nRot = 4; break;
            case (Tetrimino::Symmetry::Line): nRot = 2; break;
            case (Tetrimino::Symmetry::Point): nRot = 1; break;
            default: nRot = 0;
        }
        // keep the initial left/right positions as reference
        const int initialLeft = tetrimino->GetLeftBlock();
        const int initialRight = tetrimino->GetRightBlock();
        // initial horizontal moves
        int nLeft = position.col + initialLeft;
        int nRight = Board::Width - position.col - initialRight - 1;
        // ...
        Actions acts;
        // loop over all rotational variations
        for (int iRot = 0; iRot < nRot; iRot++, tetrimino->Rotate())
        {
            // update the possible moves sideways
            nLeft += tetrimino->GetLeftBlock() - initialLeft;
            nRight += initialRight - tetrimino->GetRightBlock();
            // loop over all variations of horizontal moves
            for (int iMove = 0; iMove < nLeft+nRight+1; iMove++)
            {
                // generate the action
                Action a;
                for (int ii = 0; ii < iRot; ii++) a.push_back(Game::Moves::Rotate);
                if (iMove <= nLeft)
                {
                    for (int ii = 0; ii < iMove; ii++) a.push_back(Game::Moves::Left);
                }
                else
                {
                    for (int ii = nLeft; ii < iMove; ii++) a.push_back(Game::Moves::Right);
                }
                a.push_back(Game::Moves::Advance);
                // add the action to the list of all possible actions
                acts.push_back(a);
            }
        }
        // rotate back to original position
        for (int ii = nRot; ii < 4; ii++)
        {
            tetrimino->Rotate();
        }
        return acts;
    }
};

#endif