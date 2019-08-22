#include <gtest/gtest.h>
#include "tetrimino.hpp"


class TetriminoFactoryTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Tetrimino square = Tetrimino::Make(Tetrimino::Type::Square);
	Tetrimino line = Tetrimino::Make(Tetrimino::Type::Line);
	Tetrimino rHook = Tetrimino::Make(Tetrimino::Type::RightHook);
	Tetrimino lHook = Tetrimino::Make(Tetrimino::Type::LeftHook);
	Tetrimino tee = Tetrimino::Make(Tetrimino::Type::Tee);
	Tetrimino rChair = Tetrimino::Make(Tetrimino::Type::RightChair);
	Tetrimino lChair = Tetrimino::Make(Tetrimino::Type::LeftChair);
};

TEST_F(TetriminoFactoryTest, Square)
{
	ASSERT_EQ(square.GetShape(0, 2, 2), 1);
	ASSERT_EQ(square.GetShape(1, 2, 1), 1);
	ASSERT_EQ(square.GetShape(2, 1, 1), 1);
	ASSERT_EQ(square.GetShape(3, 1, 2), 1);
}

TEST_F(TetriminoFactoryTest, Line)
{
	ASSERT_EQ(line.GetShape(0, 2, 2), 1);
	ASSERT_EQ(line.GetShape(1, 2, 1), 1);
	ASSERT_EQ(line.GetShape(2, 3, 1), 1);
	ASSERT_EQ(line.GetShape(3, 1, 0), 1);
}

TEST_F(TetriminoFactoryTest, RightHook)
{
	ASSERT_EQ(rHook.GetShape(0, 0, 1), 1);
	ASSERT_EQ(rHook.GetShape(1, 1, 2), 1);
	ASSERT_EQ(rHook.GetShape(2, 1, 2), 1);
	ASSERT_EQ(rHook.GetShape(3, 1, 2), 1);
}

TEST_F(TetriminoFactoryTest, LeftHook)
{
	ASSERT_EQ(lHook.GetShape(0, 0, 2), 1);
	ASSERT_EQ(lHook.GetShape(1, 2, 2), 1);
	ASSERT_EQ(lHook.GetShape(2, 1, 1), 1);
	ASSERT_EQ(lHook.GetShape(3, 2, 2), 1);
}

TEST_F(TetriminoFactoryTest, Tee)
{
	ASSERT_EQ(tee.GetShape(0, 1, 2), 1);
	ASSERT_EQ(tee.GetShape(1, 1, 1), 1);
	ASSERT_EQ(tee.GetShape(2, 1, 1), 1);
	ASSERT_EQ(tee.GetShape(3, 0, 2), 1);
}

TEST_F(TetriminoFactoryTest, RightChair)
{
	ASSERT_EQ(rChair.GetShape(0, 1, 1), 1);
	ASSERT_EQ(rChair.GetShape(1, 2, 2), 1);
	ASSERT_EQ(rChair.GetShape(2, 1, 1), 1);
	ASSERT_EQ(rChair.GetShape(3, 0, 2), 1);
}

TEST_F(TetriminoFactoryTest, LeftChair)
{
	ASSERT_EQ(lChair.GetShape(0, 2, 0), 1);
	ASSERT_EQ(lChair.GetShape(1, 1, 1), 1);
	ASSERT_EQ(lChair.GetShape(2, 2, 2), 1);
	ASSERT_EQ(lChair.GetShape(3, 2, 1), 1);
}