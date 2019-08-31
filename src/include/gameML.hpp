#ifndef GAME_ML_H
#define GAME_ML_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "game.hpp"
#include <vector>

class GameML : public Game
{
public:
    GameML() : Game() {;}
    GameML(const bool& random) : Game(random) {;}
    ~GameML() {;}

protected:
    typedef std::vector<Moves> Action;
    typedef std::vector<Action> Actions;

    const Actions& GetActions(Tetrimino* tetrimino)
    {
        size_t hash = tetrimino->GetHash();
        if (this->actions.count(hash) == 0)
        { 
            // we have to generate all possible actions
            // and add them to hash table
            this->actions[hash] = this->CreateActions(tetrimino);

        }
        return this->actions.at(hash);
    }

private:
    std::map<size_t, Actions> actions;

    Actions CreateActions(Tetrimino* tetrimino)
    {
        // check th possible enumber of rotations
        int nRot;
        switch (tetrimino->GetSymmetry())
        {
            case (Tetrimino::Symmetry::None): nRot = 4; break;
            case (Tetrimino::Symmetry::Line): nRot = 2; break;
            case (Tetrimino::Symmetry::Point): nRot = 1; break;
            default: nRot = 0;
        }

        Actions acts;
        // loop over all rotational variations
        for (int iRot = 0; iRot < nRot; iRot++)
        {
            // check the possible moves sideways

            // generate the action
            Action a;
            for (int ii = 0; ii < iRot; ii++)
            {
                a.push_back(Game::Moves::Rotate);
            }
            // add the action to the list of all possible actions
            acts.push_back(a);
        }
        return acts;
    }
};

#endif // GAME_ML_H