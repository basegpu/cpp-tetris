#include "game.hpp"
#include "board.hpp"
#include "viewer.hpp"
#include <iostream>

#define KEY_ROTATE 105
#define KEY_LEFT 106
#define KEY_DOWN 107
#define KEY_RIGHT 108
#define KEY_ADVANCE 109

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
        switch ((int)M)
        {
            case(KEY_LEFT): game->MoveLeft(); break;
            case(KEY_ROTATE): game->Rotate(); break;
            case(KEY_RIGHT): game->MoveRight(); break;
            case(KEY_DOWN): game->MoveDown(); break;
            case(KEY_ADVANCE): game->Advance(); break;
            default: break;
        }
    }
    delete game;
    return 1;
}