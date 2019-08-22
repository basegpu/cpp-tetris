#include "gtest/gtest.h"
#include "board.hpp"


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