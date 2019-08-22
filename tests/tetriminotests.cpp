#include <gtest/gtest.h>
#include "tetrimino.hpp"


class TetriminoTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Tetrimino p = Tetrimino({
		{0,0,0,0},
		{1,0,0,0},
		{0,0,2,0},
		{0,3,0,0}
	});
};

TEST_F(TetriminoTest, noRotation)
{
	ASSERT_EQ(p.GetShape(0, 0, 0), 0);
	ASSERT_EQ(p.GetShape(0, 1, 0), 1);
	ASSERT_EQ(p.GetShape(0, 2, 2), 2);
	ASSERT_EQ(p.GetShape(0, 3, 1), 3);
	ASSERT_EQ(p.GetShape(0, 0, 3), 0);
}

TEST_F(TetriminoTest, rotation90)
{
	ASSERT_EQ(p.GetShape(1, 0, 0), 0);
	ASSERT_EQ(p.GetShape(1, 0, 2), 1);
	ASSERT_EQ(p.GetShape(1, 2, 1), 2);
	ASSERT_EQ(p.GetShape(1, 1, 0), 3);
	ASSERT_EQ(p.GetShape(1, 3, 3), 0);
}

TEST_F(TetriminoTest, rotation180)
{
	ASSERT_EQ(p.GetShape(2, 0, 0), 0);
	ASSERT_EQ(p.GetShape(2, 2, 3), 1);
	ASSERT_EQ(p.GetShape(2, 1, 1), 2);
	ASSERT_EQ(p.GetShape(2, 0, 2), 3);
	ASSERT_EQ(p.GetShape(2, 1, 0), 0);
}

TEST_F(TetriminoTest, rotation270)
{
	ASSERT_EQ(p.GetShape(3, 0, 0), 0);
	ASSERT_EQ(p.GetShape(3, 3, 1), 1);
	ASSERT_EQ(p.GetShape(3, 1, 2), 2);
	ASSERT_EQ(p.GetShape(3, 2, 3), 3);
	ASSERT_EQ(p.GetShape(3, 1, 0), 0);
}