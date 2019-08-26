#include <gtest/gtest.h>
#include <stdexcept>
#include "board.hpp"
#include "tetrimino.hpp"


class BoardTest : public ::testing::Test, public Board
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
};

TEST_F(BoardTest, EmptyBoard)
{
	for (int ii = 0; ii < BOARD_WIDTH; ii++)
	{
		for (int jj = 0; jj < BOARD_HEIGHT; jj++)
		{
			ASSERT_EQ(this->IsFreeBlock(ii, jj), true);
		}
	}
}

TEST_F(BoardTest, BadBlockAccess)
{
	ASSERT_THROW(this->IsFreeBlock(100, 100), std::out_of_range);
}

TEST_F(BoardTest, SingleTetrimino)
{
	this->AddTetrimino(Tetrimino::Type::Square, 0, 0, 0);
	ASSERT_EQ(this->IsFreeBlock(0, 0), true);
	ASSERT_EQ(this->IsFreeBlock(1, 1), false);
	ASSERT_EQ(this->IsFreeBlock(2, 2), false);
	ASSERT_EQ(this->IsFreeBlock(3, 3), true);
}

TEST_F(BoardTest, TetriminoOutside)
{
	ASSERT_THROW(
		this->AddTetrimino(
			Tetrimino::Type::Line, 1,
			BOARD_WIDTH-TETRIMINO_WIDTH+1, 0),
		std::out_of_range);
	ASSERT_THROW(
		this->AddTetrimino(
			Tetrimino::Type::Line, 3,
			0, 100),
		std::out_of_range);
}

TEST_F(BoardTest, DeleteSingleLine)
{
	this->AddTetrimino(Tetrimino::Type::Line, 1, 0, 0);
	ASSERT_EQ(this->IsFreeBlock(0, 3), true);
	this->DeleteLine(10);
	ASSERT_EQ(this->IsFreeBlock(0, 3), false);
}

TEST_F(BoardTest, DeleteLineOutisde)
{
	ASSERT_THROW(this->DeleteLine(BOARD_HEIGHT), std::out_of_range);
}

TEST_F(BoardTest, GameOver)
{
	this->AddTetrimino(Tetrimino::Type::Line, 1, 0, 0);
	ASSERT_EQ(this->IsGameOver(), false);
	this->AddTetrimino(Tetrimino::Type::Line, 0, 5, 0);
	ASSERT_EQ(this->IsGameOver(), true);
}