#include "game.hpp"
#include "board.hpp"
#include "viewer.hpp"
#include <iostream>
#include <map>

#define KEY_ROTATE 105
#define KEY_LEFT 106
#define KEY_DOWN 107
#define KEY_RIGHT 108
#define KEY_ADVANCE 109

const std::map<int, Game::Moves> commands = {
    {KEY_ADVANCE, Game::Moves::Advance},
    {KEY_ROTATE,  Game::Moves::Rotate },
    {KEY_DOWN,    Game::Moves::Down   },
    {KEY_LEFT,    Game::Moves::Left   },
    {KEY_RIGHT,   Game::Moves::Right  },
};

int main(int argc, char* argv[])
{
    bool random = true;
    if (argc >= 2)
    {
        random = false;
    }
    Game* game = new Game(random);
    while (game->On())
    {
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        std::cout << "\x1B[2J\x1B[H";
        std::cout << Viewer::Print(game);
        // read key
        char M;
        std::cin >> M;
        if (commands.count((int)M))
        {
            game->MakeMove(commands.at((int)M));
        }
    }
    delete game;
    return 1;
}