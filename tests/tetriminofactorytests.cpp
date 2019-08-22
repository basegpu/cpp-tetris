#include "gtest/gtest.h"
#include "tetrimino.hpp"


class TetriminoFactoryTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Tetrimino square = Tetrimino::make(Tetrimino::Type::Square);
	Tetrimino line = Tetrimino::make(Tetrimino::Type::Line);
	Tetrimino rHook = Tetrimino::make(Tetrimino::Type::RightHook);
	Tetrimino lHook = Tetrimino::make(Tetrimino::Type::LeftHook);
	Tetrimino tee = Tetrimino::make(Tetrimino::Type::Tee);
	Tetrimino rChair = Tetrimino::make(Tetrimino::Type::RightChair);
	Tetrimino lChair = Tetrimino::make(Tetrimino::Type::LeftChair);
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

TEST_F(TetriminoFactoryTest, Tee)
{
	ASSERT_EQ(tee.getShape(0, 1, 2), 1);
	ASSERT_EQ(tee.getShape(1, 1, 1), 1);
	ASSERT_EQ(tee.getShape(2, 1, 1), 1);
	ASSERT_EQ(tee.getShape(3, 0, 2), 1);
}

TEST_F(TetriminoFactoryTest, RightChair)
{
	ASSERT_EQ(rChair.getShape(0, 1, 1), 1);
	ASSERT_EQ(rChair.getShape(1, 2, 2), 1);
	ASSERT_EQ(rChair.getShape(2, 1, 1), 1);
	ASSERT_EQ(rChair.getShape(3, 0, 2), 1);
}

TEST_F(TetriminoFactoryTest, LeftChair)
{
	ASSERT_EQ(lChair.getShape(0, 2, 0), 1);
	ASSERT_EQ(lChair.getShape(1, 1, 1), 1);
	ASSERT_EQ(lChair.getShape(2, 2, 2), 1);
	ASSERT_EQ(lChair.getShape(3, 2, 1), 1);
}