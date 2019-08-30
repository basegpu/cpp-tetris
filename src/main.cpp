#include "game.hpp"
#include "board.hpp"
#include "viewer.hpp"
#include <iostream>
#include <sstream>
#include <map>
#include <vector>
#include <string>

const std::map<char, Game::Moves> commands = {
    {'m', Game::Moves::Advance},
    {'i', Game::Moves::Rotate },
    {'k', Game::Moves::Down   },
    {'j', Game::Moves::Left   },
    {'l', Game::Moves::Right  },
};

const std::vector<Game::Moves> parseCommandLineArguments(int argc, char* argv[])
{
    std::vector<Game::Moves> moves;
    if (argc == 2)
    {
        std::string seq = std::string(argv[1]);
        for (const char& c : seq)
        {
            if (commands.count((int)c))
            {
                moves.push_back(commands.at((int)c));
            }
        }
    }
    return moves;
}

const std::string printUsage()
{
    std::ostringstream out;
    out << "j -> move left" << std::endl;
    out << "l -> move right" << std::endl;
    out << "k -> move down" << std::endl;
    out << "i -> rotate" << std::endl;
    out << "m -> drop" << std::endl;
    return out.str();
}

void viewGame(const Game* game)
{
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";
    std::cout << Viewer::Print(game);
    std::cout << std::endl << printUsage();
}


int main(int argc, char* argv[])
{
    Game* game = nullptr;
    // parse command line
    auto moves = parseCommandLineArguments(argc, argv);
    // create game
    if (moves.size())
    {
        // play given deterministic sequence first
        game = new Game(false);
        game->PlaySequence(moves);
    }
    else
    {
        game = new Game(true);
    }
    // then go gon with user input
    char M;
    while (game->On())
    {
        viewGame(game);
        // read key
        std::cin >> M;
        // try to make a move
        try
        {
            game->MakeMove(commands.at(M));
        }
        catch (...) {} // bad key
    }
    delete game;
    return 1;
}