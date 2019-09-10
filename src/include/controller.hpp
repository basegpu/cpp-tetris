#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "game.hpp"
#include "viewer.hpp"
#include <string>
#include <unordered_map>

class Controller
{
public:
    Controller();
    ~Controller();
    
    void CreateGame(int argc, char* argv[]);
    void RunGame();

private:
    static const std::unordered_map<char, Moves> commands;
    bool isRandom;
    bool showBoard;
    bool autoPlay;
    bool bestPlay;
    int sleepTime;
    std::string initSequence;
    Game* game;

    static const std::string PrintUsage();
    void ParseCommandLine(int argc, char* argv[]);
    void ViewGame() const;
};

#endif