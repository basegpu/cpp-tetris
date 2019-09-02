#include "game.hpp"
#include "controller.hpp"
#include "viewer.hpp"
#include <tclap/CmdLine.h>
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>


const std::map<char, Game::Moves> Controller::commands = {
    {'m', Game::Moves::Advance},
    {'i', Game::Moves::Rotate },
    {'k', Game::Moves::Down   },
    {'j', Game::Moves::Left   },
    {'l', Game::Moves::Right  },
};

const std::string Controller::PrintUsage()
{
    std::ostringstream out;
    out << "j -> move left" << std::endl;
    out << "l -> move right" << std::endl;
    out << "k -> move down" << std::endl;
    out << "i -> rotate" << std::endl;
    out << "m -> drop" << std::endl;
    return out.str();
}

Controller::Controller() :
    isRandom(true),
    initSequence(""),
    game(nullptr)
{
    ;
}

Controller::~Controller()
{
    if (this->game) delete game;
}

void Controller::CreateGame(int argc, char* argv[])
{
    this->ParseCommandLine(argc, argv);
    std::vector<Game::Moves> moves;
    for (const char& c : this->initSequence)
    {
        try
        {
            moves.push_back(commands.at(c));
        }
        catch (...) {} // bad char
    }
    // create game
    this->game = new Game(this->isRandom);
    // eventually play a given sequence first
    if (moves.size())
    {
        this->game->PlaySequence(moves);
    }

}

void Controller::RunGame()
{
    // process user input
    char M;
    while (this->game->On())
    {
        this->ViewGame();
        // read key
        std::cin >> M;
        // try to make a move
        try
        {
            this->game->MakeMove(commands.at(M));
        }
        catch (...) {} // bad key
    }
}

void Controller::ParseCommandLine(int argc, char* argv[])
{
    try
    {
        TCLAP::CmdLine cmd("This is a tetris game engine", ' ', "0.9");
        TCLAP::ValueArg<std::string> sequenceArg("s", "sequence", "play sequence of commands initially", false, "", "string", cmd);
        TCLAP::SwitchArg reproArg("r", "reproducible", "non-random, reproducible game", cmd, false);
        cmd.parse(argc, argv);
        // Get the value parsed by each arg.
        this->initSequence = sequenceArg.getValue();
        this->isRandom = !reproArg.getValue();
    }
    catch (TCLAP::ArgException &e)
    {
        TETRIS_ERROR(e.error() << " for arg " << e.argId());
    }
}

void Controller::ViewGame() const
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
    std::cout << Viewer::Print(this->game);
    std::cout << std::endl << this->PrintUsage();
}