#include "game.hpp"
#include "controller.hpp"
#include "viewer.hpp"
#include "monitor.hpp"
#include <tclap/CmdLine.h>
#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <chrono>
#include <thread>
#include <cmath>

using namespace std::chrono;

const std::unordered_map<char, Moves> Controller::commands = {
    {'m', Moves::Advance},
    {'i', Moves::Rotate },
    {'k', Moves::Down   },
    {'j', Moves::Left   },
    {'l', Moves::Right  },
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
    this->ParseCommandLine(argc, argv);
    // eventually seed random numbers
    SetRandom(this->isRandom);
    // create initial moves
    std::vector<Moves> moves;
    for (const char& c : this->initSequence)
    {
        try
        {
            moves.push_back(commands.at(c));
        }
        catch (...) {} // bad char
    }
    // create game
    this->game = new Game();
    // eventually play a given sequence first
    if (moves.size())
    {
        this->game->PlaySequence(moves);
    }

}

void Controller::RunGame()
{
    Monitor m;
    high_resolution_clock::time_point t_start, t_end;
    double t_spent;
    int count = 0;
    while (count++ < this->nGames)
    {
        t_start = high_resolution_clock::now();
        this->RunGameOnce();
        t_end = high_resolution_clock::now();
        t_spent = duration_cast<duration<double>>(t_end - t_start).count();
        m.AddOutput(
            this->game->GetScore(),
            t_spent/this->game->GetScore()*1000);
    }
    m.Print();
}

void Controller::ParseCommandLine(int argc, char* argv[])
{
    try
    {
        TCLAP::CmdLine cmd("This is a tetris game engine", ' ', "0.9");
        TCLAP::ValueArg<std::string> sequenceArg("i", "initial", "play sequence of commands initially", false, "", "string", cmd);
        TCLAP::ValueArg<int> sleepArg("p", "pause", "sleeping time in milli seconds between moves", false, 100, "int", cmd);
        TCLAP::ValueArg<int> nArg("n", "number", "number of games to be played", false, 1, "int", cmd);
        TCLAP::SwitchArg reproArg("r", "reproducible", "non-random, reproducible game", cmd, false);
        TCLAP::SwitchArg autoArg("a", "auto", "auto-play mode", cmd, false);
        TCLAP::ValueArg<int> strategyArg("s", "strategy", "playing strategy of auto-mode", false, 0, "int", cmd);
        TCLAP::SwitchArg quietArg("q", "quiet", "don't show the board after each move", cmd, false);
        cmd.parse(argc, argv);
        // Get the value parsed by each arg.
        this->initSequence = sequenceArg.getValue();
        this->sleepTime = sleepArg.getValue();
        this->nGames = nArg.getValue();
        this->isRandom = !reproArg.getValue();
        this->showBoard = !quietArg.getValue();
        this->autoPlay = autoArg.getValue();
        this->strategy = strategyArg.getValue();
    }
    catch (TCLAP::ArgException &e)
    {
        TETRIS_ERROR(e.error() << " for arg " << e.argId());
    }
}

void Controller::RunGameOnce()
{
    this->game->Reset();
    // process user input
    char M;
    while (this->game->On())
    {
        if (this->showBoard)
        {
            this->ViewGame(true);
        }
        if (this->autoPlay)
        {
            std::chrono::milliseconds pause(this->sleepTime);
            std::this_thread::sleep_for(pause);
            this->game->SelfPlay(this->strategy);
        }
        else
        {
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
}

void Controller::ViewGame(const bool& clean) const
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    if (clean)
    {
        std::cout << "\x1B[2J\x1B[H";
    }
    std::cout << Viewer::Print(*this->game);
    if (!this->autoPlay)
    {
        std::cout << std::endl << this->PrintUsage();
    }
}