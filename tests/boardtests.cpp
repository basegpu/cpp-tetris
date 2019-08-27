#include <gtest/gtest.h>
#include <stdexcept>
#include "board.hpp"
#include "tetrimino.hpp"


class BoardTest : public ::testing::Test, public Board
{
protected:
	void SetUp() override
	{
		square = Tetrimino::Make(Tetrimino::Type::Square, 0);
		line0 = Tetrimino::Make(Tetrimino::Type::Line, 0);
		line90 = Tetrimino::Make(Tetrimino::Type::Line, 1);
		line270 = Tetrimino::Make(Tetrimino::Type::Line, 3);
		lHook = Tetrimino::Make(Tetrimino::Type::LeftHook, 2);
	}
	void TearDown() override
	{
		delete square;
		delete line0;
		delete line90;
		delete line270;
		delete lHook;
	}
	Tetrimino *square, *line0, *line90, *line270, *lHook;
};

TEST_F(BoardTest, EmptyBoard)
{
	this->Reset();
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
	this->Reset();
	this->AddTetrimino(this->square, 0, 0);
	ASSERT_EQ(this->IsFreeBlock(0, 0), true);
	ASSERT_EQ(this->IsFreeBlock(1, 1), false);
	ASSERT_EQ(this->IsFreeBlock(2, 2), false);
	ASSERT_EQ(this->IsFreeBlock(3, 3), true);
}

TEST_F(BoardTest, TetriminoOutside)
{
	ASSERT_THROW(
		this->AddTetrimino(
			this->line90,
			BOARD_WIDTH-TETRIMINO_WIDTH+1, 0),
		std::out_of_range);
	ASSERT_THROW(
		this->AddTetrimino(
			this->line270,
			0, 100),
		std::out_of_range);
}

TEST_F(BoardTest, DeleteSingleLine)
{
	this->Reset();
	this->AddTetrimino(this->line90, 0, 0);
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
	this->Reset();
	this->AddTetrimino(this->line90, 0, 0);
	ASSERT_EQ(this->IsGameOver(), false);
	this->AddTetrimino(this->line0, 5, 0);
	ASSERT_EQ(this->IsGameOver(), true);
}

TEST_F(BoardTest, DeletePossibleLines)
{
	this->Reset();
	this->AddTetrimino(this->line90, 0, 17);
	this->AddTetrimino(this->line90, 4, 17);
	this->AddTetrimino(this->line0, 6, 16);
	this->AddTetrimino(this->line0, 7, 16);
	ASSERT_EQ(this->CountFilledBlocks(), 16);
	this->DeletePossibleLines();
	ASSERT_EQ(this->CountFilledBlocks(), 6);
}

TEST_F(BoardTest, PossibleMoves)
{
	this->Reset();
	this->AddTetrimino(this->line90, 0, 17);
	this->AddTetrimino(this->line90, 4, 17);
	this->AddTetrimino(this->line90, 4, 16);
	this->AddTetrimino(this->line0, 6, 16);
	this->AddTetrimino(this->line0, 7, 16);
	ASSERT_EQ(this->IsPossibleMove(this->square, 4, 4), true);
	ASSERT_EQ(this->IsPossibleMove(this->square, 7, 13), true);
	ASSERT_EQ(this->IsPossibleMove(this->square, 8, 13), false);
	ASSERT_EQ(this->IsPossibleMove(this->square, 7, 14), false);
	ASSERT_EQ(this->IsPossibleMove(this->lHook, 6, 14), true);
}
