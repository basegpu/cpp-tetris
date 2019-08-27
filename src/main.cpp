#include "game.hpp"
#include "board.hpp"
#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
	Game game;
	while (game.On())
	{
		game.Print(std::cout);
		int n = std::rand() % (Board::Width/2);
		int lr = std::rand() % 2;
		for (int ii = 0; ii < n; ii++)
		{
			if (lr == 0)
				game.MoveLeft();
			else
				game.MoveRight();
		}
		game.Advance();	
	}
	return 1;
}