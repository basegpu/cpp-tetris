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
    static const std::map<char, Moves> commands;
    bool isRandom;
    bool autoPlay;
    std::string initSequence;
    Game* game;

    static const std::string PrintUsage();
    void ParseCommandLine(int argc, char* argv[]);
    void ViewGame(const bool& withUsage) const;
};

#endif