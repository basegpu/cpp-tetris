#ifndef GAME_ML_H
#define GAME_ML_H

#include "globals.hpp"
#include "tetrimino.hpp"
#include "game.hpp"
#include "actions.hpp"
#include <map>

class GameML : public Game
{
public:
    GameML() : Game() {;}
    GameML(const bool& random) : Game(random) {;}
    ~GameML() {;}

protected:
    std::map<size_t, Actions> actionsRegistry;

    const Actions& GetActions(Tetrimino* tetrimino)
    {
        size_t hash = tetrimino->GetHash();
        if (this->actionsRegistry.count(hash) == 0)
        { 
            // we have to generate all possible actions
            // and add them to hash table
            this->actionsRegistry[hash] = Actions::CreateFor(tetrimino, this->currentPosition);
        }
        return this->actionsRegistry.at(hash);
    }
};

#endif // GAME_ML_H