#include "gtest/gtest.h"
#include "tetrimino.hpp"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

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
	ASSERT_EQ(p.getShape(0, 0, 0), 0);
	ASSERT_EQ(p.getShape(0, 1, 0), 1);
	ASSERT_EQ(p.getShape(0, 2, 2), 2);
	ASSERT_EQ(p.getShape(0, 3, 1), 3);
	ASSERT_EQ(p.getShape(0, 0, 3), 0);
}

TEST_F(TetriminoTest, rotation90)
{
	ASSERT_EQ(p.getShape(1, 0, 0), 0);
	ASSERT_EQ(p.getShape(1, 0, 2), 1);
	ASSERT_EQ(p.getShape(1, 2, 1), 2);
	ASSERT_EQ(p.getShape(1, 1, 0), 3);
	ASSERT_EQ(p.getShape(1, 3, 3), 0);
}

TEST_F(TetriminoTest, rotation180)
{
	ASSERT_EQ(p.getShape(2, 0, 0), 0);
	ASSERT_EQ(p.getShape(2, 2, 3), 1);
	ASSERT_EQ(p.getShape(2, 1, 1), 2);
	ASSERT_EQ(p.getShape(2, 0, 2), 3);
	ASSERT_EQ(p.getShape(2, 1, 0), 0);
}

TEST_F(TetriminoTest, rotation270)
{
	ASSERT_EQ(p.getShape(3, 0, 0), 0);
	ASSERT_EQ(p.getShape(3, 3, 1), 1);
	ASSERT_EQ(p.getShape(3, 1, 2), 2);
	ASSERT_EQ(p.getShape(3, 2, 3), 3);
	ASSERT_EQ(p.getShape(3, 1, 0), 0);
}


class TetriminoFactoryTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Tetrimino square = makePiece(Tetrimino::Type::Square);
	Tetrimino line = makePiece(Tetrimino::Type::Line);
};

TEST_F(TetriminoFactoryTest, badType)
{
	ASSERT_ANY_THROW(makePiece(Tetrimino::Type::None));
}

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