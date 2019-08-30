#include <gtest/gtest.h>
#include <vector>
#include "game.hpp"


class GameTest : public ::testing::Test, public Game
{
protected:
    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(GameTest, Init)
{
    ASSERT_NE(this->board, nullptr);
    ASSERT_NE(this->piece, nullptr);
    ASSERT_NE(this->nextPiece, nullptr);
}

TEST_F(GameTest, NewPiece)
{
    Tetrimino* p = this->nextPiece;
    this->AddNewPiece();
    ASSERT_EQ(this->piece, p);
}

TEST(NonRandomGameTest, PlaySequence)
{
	Game* game = new Game(false);
	ASSERT_EQ(game->GetScore(), 0);
	// moves represented by console input 'jjjjmillllmlmiijmijjjjjmimlmlmijmiillllmiiilllmijjjm'
	std::vector<Game::Moves> moves = {
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Advance,
		Game::Moves::Right,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Rotate,
		Game::Moves::Left,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Advance,
		Game::Moves::Right,
		Game::Moves::Advance,
		Game::Moves::Right,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Left,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Rotate,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Rotate,
		Game::Moves::Rotate,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Right,
		Game::Moves::Advance,
		Game::Moves::Rotate,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Left,
		Game::Moves::Advance
	};
	game->PlaySequence(moves);
	ASSERT_EQ(game->GetScore(), 2);
	delete game;
}
