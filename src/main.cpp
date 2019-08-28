#include "game.hpp"
#include "board.hpp"
#include "viewer.hpp"
#include <iostream>
#include <sstream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    int M;
    Game* game = new Game();
    while (game->On())
    {
        // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
        std::cout << "\x1B[2J\x1B[H";
        std::cout << Viewer::Print(game);
        // read key
        std::cin >> M;
        switch (M)
        {
            case(1): game->MoveLeft(); break;
            case(2): game->Rotate(); break;
            case(3): game->MoveRight(); break;
            case(4): game->Advance(); break;
            default: break;
        }
    }
    delete game;
    return 1;
}