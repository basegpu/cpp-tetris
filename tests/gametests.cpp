#include <gtest/gtest.h>
#include "game.hpp"


class GameTest : public ::testing::Test, public Game
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
};

TEST_F(GameTest, Init)
{
	ASSERT_NE(this->piece, nullptr);
}

TEST_F(GameTest, NewPiece)
{
	Tetrimino* p = this->nextPiece;
	this->AddNewPiece();
	ASSERT_EQ(this->piece, p);
}
