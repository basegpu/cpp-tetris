#include "game.hpp"
#include "controller.hpp"
#include "viewer.hpp"
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
    std::vector<Game::Moves> moves;
    if (argc == 2)
    {
        std::string seq = std::string(argv[1]);
        for (const char& c : seq)
        {
            try
            {
                moves.push_back(commands.at(c));
            }
            catch (...) {} // bad char
        }
    }
    // create game
    if (moves.size())
    {
        // play given deterministic sequence first
        this->game = new Game(false);
        this->game->PlaySequence(moves);
    }
    else
    {
        // regular randomized game
        this->game = new Game(true);
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

void Controller::ViewGame() const
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
    std::cout << Viewer::Print(this->game);
    std::cout << std::endl << this->PrintUsage();
}