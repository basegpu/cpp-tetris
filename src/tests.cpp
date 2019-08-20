#include "gtest/gtest.h"
#include "pieces.hpp"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

class PieceTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
	Piece p = Piece({
		{0,0,0,0,0},
		{1,0,0,0,0},
		{0,0,2,0,0},
		{0,3,0,0,0},
		{0,0,0,0,0}
	});
};

TEST_F(PieceTest, noRotation)
{
	ASSERT_EQ(p.getShape(0, 0, 0), 0);
	ASSERT_EQ(p.getShape(0, 1, 0), 1);
	ASSERT_EQ(p.getShape(0, 2, 2), 2);
	ASSERT_EQ(p.getShape(0, 3, 1), 3);
	ASSERT_EQ(p.getShape(0, 0, 4), 0);
}