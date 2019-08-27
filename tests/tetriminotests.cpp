#include <gtest/gtest.h>
#include "tetrimino.hpp"


class TetriminoTest :
	public ::testing::Test,
	public Tetrimino
{
public:
	TetriminoTest() :
		Tetrimino({
			{0,0,0,0},
			{1,0,0,0},
			{0,0,2,0},
			{0,3,0,0}
		})
	{}
protected:
	// void SetUp() override {}
	// void TearDown() override {}
};

TEST_F(TetriminoTest, nBlocks)
{
	ASSERT_EQ(Tetrimino::BlocksPerPiece, 4);
}

TEST_F(TetriminoTest, NoRotationShape)
{
	ASSERT_EQ(this->GetShape(0, 0, 0), 0);
	ASSERT_EQ(this->GetShape(0, 1, 0), 1);
	ASSERT_EQ(this->GetShape(0, 2, 2), 2);
	ASSERT_EQ(this->GetShape(0, 3, 1), 3);
	ASSERT_EQ(this->GetShape(0, 0, 3), 0);
}

TEST_F(TetriminoTest, NoRotationTopLeft)
{
	ASSERT_EQ(this->GetTopBlock(0), 1);
	ASSERT_EQ(this->GetLeftBlock(0), 0);
}

TEST_F(TetriminoTest, Rotation90Shape)
{
	ASSERT_EQ(this->GetShape(1, 0, 0), 0);
	ASSERT_EQ(this->GetShape(1, 0, 2), 1);
	ASSERT_EQ(this->GetShape(1, 2, 1), 2);
	ASSERT_EQ(this->GetShape(1, 1, 0), 3);
	ASSERT_EQ(this->GetShape(1, 3, 3), 0);
}

TEST_F(TetriminoTest, Rotation90Position)
{
	ASSERT_EQ(this->GetTopBlock(1), 0);
	ASSERT_EQ(this->GetLeftBlock(1), 0);
}

TEST_F(TetriminoTest, Rotation180Shape)
{
	ASSERT_EQ(this->GetShape(2, 0, 0), 0);
	ASSERT_EQ(this->GetShape(2, 2, 3), 1);
	ASSERT_EQ(this->GetShape(2, 1, 1), 2);
	ASSERT_EQ(this->GetShape(2, 0, 2), 3);
	ASSERT_EQ(this->GetShape(2, 1, 0), 0);
}

TEST_F(TetriminoTest, Rotation180Position)
{
	ASSERT_EQ(this->GetTopBlock(2), 0);
	ASSERT_EQ(this->GetLeftBlock(2), 1);
}

TEST_F(TetriminoTest, Rotation270Shape)
{
	ASSERT_EQ(this->GetShape(3, 0, 0), 0);
	ASSERT_EQ(this->GetShape(3, 3, 1), 1);
	ASSERT_EQ(this->GetShape(3, 1, 2), 2);
	ASSERT_EQ(this->GetShape(3, 2, 3), 3);
	ASSERT_EQ(this->GetShape(3, 1, 0), 0);
}

TEST_F(TetriminoTest, Rotation270Position)
{
	ASSERT_EQ(this->GetTopBlock(3), 1);
	ASSERT_EQ(this->GetLeftBlock(3), 1);
}