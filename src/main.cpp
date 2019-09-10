#include "controller.hpp"
#include <exception>


int main(int argc, char* argv[])
{
    try
    {
        Controller c;
        c.CreateGame(argc, argv);
        c.RunGame();
    }
    catch (const std::exception& e)
    {
        TETRIS_ERROR("something went wrong: " << e.what())
        return 1;
    }
    return 0;
}