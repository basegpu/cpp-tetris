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

TEST_F(TetriminoFactoryTest, SquareShape)
{
	ASSERT_EQ(square.GetShape(0, 2, 2), 1);
	ASSERT_EQ(square.GetShape(1, 2, 1), 1);
	ASSERT_EQ(square.GetShape(2, 1, 1), 1);
	ASSERT_EQ(square.GetShape(3, 1, 2), 1);
}

TEST_F(TetriminoFactoryTest, SquareTopLeft)
{
	ASSERT_EQ(square.GetTopBlock(0), 1);
	ASSERT_EQ(square.GetLeftBlock(0), 1);
	ASSERT_EQ(square.GetTopBlock(1), 1);
	ASSERT_EQ(square.GetLeftBlock(1), 1);
	ASSERT_EQ(square.GetTopBlock(2), 1);
	ASSERT_EQ(square.GetLeftBlock(2), 1);
	ASSERT_EQ(square.GetTopBlock(3), 1);
	ASSERT_EQ(square.GetLeftBlock(3), 1);
}

TEST_F(TetriminoFactoryTest, LinePosition)
{
	ASSERT_EQ(line.GetShape(0, 2, 2), 1);
	ASSERT_EQ(line.GetShape(1, 2, 1), 1);
	ASSERT_EQ(line.GetShape(2, 3, 1), 1);
	ASSERT_EQ(line.GetShape(3, 1, 0), 1);
}

TEST_F(TetriminoFactoryTest, LineTopLeft)
{
	ASSERT_EQ(line.GetTopBlock(0), 0);
	ASSERT_EQ(line.GetLeftBlock(0), 2);
	ASSERT_EQ(line.GetTopBlock(1), 2);
	ASSERT_EQ(line.GetLeftBlock(1), 0);
	ASSERT_EQ(line.GetTopBlock(2), 0);
	ASSERT_EQ(line.GetLeftBlock(2), 1);
	ASSERT_EQ(line.GetTopBlock(3), 1);
	ASSERT_EQ(line.GetLeftBlock(3), 0);
}

TEST_F(TetriminoFactoryTest, RightHookShape)
{
	ASSERT_EQ(rHook.GetShape(0, 0, 1), 1);
	ASSERT_EQ(rHook.GetShape(1, 1, 2), 1);
	ASSERT_EQ(rHook.GetShape(2, 1, 2), 1);
	ASSERT_EQ(rHook.GetShape(3, 1, 2), 1);
}

TEST_F(TetriminoFactoryTest, RightHookTopLeft)
{
	ASSERT_EQ(rHook.GetTopBlock(0), 0);
	ASSERT_EQ(rHook.GetLeftBlock(0), 1);
	ASSERT_EQ(rHook.GetTopBlock(1), 1);
	ASSERT_EQ(rHook.GetLeftBlock(1), 1);
	ASSERT_EQ(rHook.GetTopBlock(2), 1);
	ASSERT_EQ(rHook.GetLeftBlock(2), 1);
	ASSERT_EQ(rHook.GetTopBlock(3), 1);
	ASSERT_EQ(rHook.GetLeftBlock(3), 0);
}

TEST_F(TetriminoFactoryTest, LeftHookShape)
{
	ASSERT_EQ(lHook.GetShape(0, 0, 2), 1);
	ASSERT_EQ(lHook.GetShape(1, 2, 2), 1);
	ASSERT_EQ(lHook.GetShape(2, 1, 1), 1);
	ASSERT_EQ(lHook.GetShape(3, 2, 2), 1);
}

TEST_F(TetriminoFactoryTest, LeftHookTopLeft)
{
	ASSERT_EQ(lHook.GetTopBlock(0), 0);
	ASSERT_EQ(lHook.GetLeftBlock(0), 1);
	ASSERT_EQ(lHook.GetTopBlock(1), 1);
	ASSERT_EQ(lHook.GetLeftBlock(1), 1);
	ASSERT_EQ(lHook.GetTopBlock(2), 1);
	ASSERT_EQ(lHook.GetLeftBlock(2), 1);
	ASSERT_EQ(lHook.GetTopBlock(3), 1);
	ASSERT_EQ(lHook.GetLeftBlock(3), 0);
}

TEST_F(TetriminoFactoryTest, TeeShape)
{
	ASSERT_EQ(tee.GetShape(0, 1, 2), 1);
	ASSERT_EQ(tee.GetShape(1, 1, 1), 1);
	ASSERT_EQ(tee.GetShape(2, 1, 1), 1);
	ASSERT_EQ(tee.GetShape(3, 0, 2), 1);
}

TEST_F(TetriminoFactoryTest, TeeTopLeft)
{
	ASSERT_EQ(tee.GetTopBlock(0), 1);
	ASSERT_EQ(tee.GetLeftBlock(0), 1);
	ASSERT_EQ(tee.GetTopBlock(1), 1);
	ASSERT_EQ(tee.GetLeftBlock(1), 1);
	ASSERT_EQ(tee.GetTopBlock(2), 1);
	ASSERT_EQ(tee.GetLeftBlock(2), 0);
	ASSERT_EQ(tee.GetTopBlock(3), 0);
	ASSERT_EQ(tee.GetLeftBlock(3), 1);
}

TEST_F(TetriminoFactoryTest, RightChairShape)
{
	ASSERT_EQ(rChair.GetShape(0, 1, 1), 1);
	ASSERT_EQ(rChair.GetShape(1, 2, 2), 1);
	ASSERT_EQ(rChair.GetShape(2, 1, 1), 1);
	ASSERT_EQ(rChair.GetShape(3, 0, 2), 1);
}

TEST_F(TetriminoFactoryTest, RightChairTopLeft)
{
	ASSERT_EQ(rChair.GetTopBlock(0), 1);
	ASSERT_EQ(rChair.GetLeftBlock(0), 1);
	ASSERT_EQ(rChair.GetTopBlock(1), 1);
	ASSERT_EQ(rChair.GetLeftBlock(1), 1);
	ASSERT_EQ(rChair.GetTopBlock(2), 1);
	ASSERT_EQ(rChair.GetLeftBlock(2), 0);
	ASSERT_EQ(rChair.GetTopBlock(3), 0);
	ASSERT_EQ(rChair.GetLeftBlock(3), 1);
}

TEST_F(TetriminoFactoryTest, LeftChairShape)
{
	ASSERT_EQ(lChair.GetShape(0, 2, 0), 1);
	ASSERT_EQ(lChair.GetShape(1, 1, 1), 1);
	ASSERT_EQ(lChair.GetShape(2, 2, 2), 1);
	ASSERT_EQ(lChair.GetShape(3, 2, 1), 1);
}

TEST_F(TetriminoFactoryTest, LeftChairTopLeft)
{
	ASSERT_EQ(lChair.GetTopBlock(0), 1);
	ASSERT_EQ(lChair.GetLeftBlock(0), 0);
	ASSERT_EQ(lChair.GetTopBlock(1), 0);
	ASSERT_EQ(lChair.GetLeftBlock(1), 1);
	ASSERT_EQ(lChair.GetTopBlock(2), 1);
	ASSERT_EQ(lChair.GetLeftBlock(2), 1);
	ASSERT_EQ(lChair.GetTopBlock(3), 1);
	ASSERT_EQ(lChair.GetLeftBlock(3), 1);
}