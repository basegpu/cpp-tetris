#include <gtest/gtest.h>
#include <stdexcept>
#include "board.hpp"
#include "tetrimino.hpp"


class BoardTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Board board = Board(400);
};

TEST_F(BoardTest, EmptyBoard)
{
	for (int ii = 0; ii < BOARD_WIDTH; ii++)
	{
		for (int jj = 0; jj < BOARD_HEIGHT; jj++)
		{
			ASSERT_EQ(board.IsFreeBlock(ii, jj), true);
		}
	}
}

TEST_F(BoardTest, BadBlockAccess)
{
	ASSERT_THROW(board.IsFreeBlock(100, 100), std::out_of_range);
}

TEST_F(BoardTest, singleTetrimino)
{
	board.AddTetrimino(Tetrimino::Type::Square, 0, 0, 0);
	ASSERT_EQ(board.IsFreeBlock(0, 0), true);
	ASSERT_EQ(board.IsFreeBlock(1, 1), false);
	ASSERT_EQ(board.IsFreeBlock(2, 2), false);
	ASSERT_EQ(board.IsFreeBlock(3, 3), true);
}

TEST_F(BoardTest, tetriminoOutside)
{
	ASSERT_THROW(
		board.AddTetrimino(
			Tetrimino::Type::Line, 1,
			BOARD_WIDTH-TETRIMINO_WIDTH+1, 0),
		std::out_of_range);
	ASSERT_THROW(
		board.AddTetrimino(
			Tetrimino::Type::Line, 3,
			0, 100),
		std::out_of_range);
}

TEST_F(BoardTest, gameOver)
{
	board.AddTetrimino(Tetrimino::Type::Line, 1, 0, 0);
	ASSERT_EQ(board.IsGameOver(), false);
	board.AddTetrimino(Tetrimino::Type::Line, 0, 5, 0);
	ASSERT_EQ(board.IsGameOver(), true);
}
