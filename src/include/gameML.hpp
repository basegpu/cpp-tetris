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

    Actions CreateActions(Tetrimino* tetrimino)
    {
        Actions acts;
        return acts;
    }

private:
    std::map<size_t, Actions> actions;
};

#endif // GAME_ML_H