#include "gtest/gtest.h"
#include "tetrimino.hpp"


class TetriminoFactoryTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Tetrimino square = makePiece(Tetrimino::Type::Square);
	Tetrimino line = makePiece(Tetrimino::Type::Line);
	Tetrimino rHook = makePiece(Tetrimino::Type::RightHook);
	Tetrimino lHook = makePiece(Tetrimino::Type::LeftHook);
};

TEST_F(TetriminoFactoryTest, Square)
{
	ASSERT_EQ(square.getShape(0, 2, 2), 1);
	ASSERT_EQ(square.getShape(1, 2, 1), 1);
	ASSERT_EQ(square.getShape(2, 1, 1), 1);
	ASSERT_EQ(square.getShape(3, 1, 2), 1);
}

TEST_F(TetriminoFactoryTest, Line)
{
	ASSERT_EQ(line.getShape(0, 2, 2), 1);
	ASSERT_EQ(line.getShape(1, 2, 1), 1);
	ASSERT_EQ(line.getShape(2, 3, 1), 1);
	ASSERT_EQ(line.getShape(3, 1, 0), 1);
}

TEST_F(TetriminoFactoryTest, RightHook)
{
	ASSERT_EQ(rHook.getShape(0, 0, 1), 1);
	ASSERT_EQ(rHook.getShape(1, 1, 2), 1);
	ASSERT_EQ(rHook.getShape(2, 1, 2), 1);
	ASSERT_EQ(rHook.getShape(3, 1, 2), 1);
}

TEST_F(TetriminoFactoryTest, LeftHook)
{
	ASSERT_EQ(lHook.getShape(0, 0, 2), 1);
	ASSERT_EQ(lHook.getShape(1, 2, 2), 1);
	ASSERT_EQ(lHook.getShape(2, 1, 1), 1);
	ASSERT_EQ(lHook.getShape(3, 2, 2), 1);
}