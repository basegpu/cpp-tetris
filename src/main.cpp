#include "controller.hpp"
#include <iostream>


int main(int argc, char* argv[])
{
    Controller c;
    c.CreateGame(argc, argv);
    c.RunGame();
    return 1;
}