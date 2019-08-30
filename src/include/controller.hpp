#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game.hpp"
#include "viewer.hpp"
#include <string>
#include <map>

class Controller
{
public:
    Controller();
    ~Controller();
    
    void CreateGame(int argc, char* argv[]);
    void RunGame();

private:
    static const std::map<char, Game::Moves> commands;
    Game* game;

    static const std::string PrintUsage();
    void ViewGame() const;
};

#endif