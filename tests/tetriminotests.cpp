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
        }, Tetrimino::Symmetry::None, 0)
    {}
protected:
    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(TetriminoTest, nBlocks)
{
    ASSERT_EQ(Tetrimino::BlocksPerPiece, 4);
}

TEST_F(TetriminoTest, Symmetry)
{
    ASSERT_EQ(Tetrimino::Symmetry::None, this->GetSymmetry());
}

TEST_F(TetriminoTest, NoRotationShape)
{
    this->SetRotation(0);
    ASSERT_EQ(this->GetShape(0, 0), 0);
    ASSERT_EQ(this->GetShape(1, 0), 1);
    ASSERT_EQ(this->GetShape(2, 2), 2);
    ASSERT_EQ(this->GetShape(3, 1), 3);
    ASSERT_EQ(this->GetShape(0, 3), 0);
}

TEST_F(TetriminoTest, NoRotationCorner)
{
    this->SetRotation(0);
    ASSERT_EQ(this->GetTopBlock(), 1);
    ASSERT_EQ(this->GetLeftBlock(), 0);
    ASSERT_EQ(this->GetBottomBlock(), 3);
    ASSERT_EQ(this->GetRightBlock(), 2);
}

TEST_F(TetriminoTest, Rotation90Shape)
{
    this->SetRotation(1);
    ASSERT_EQ(this->GetShape(0, 0), 0);
    ASSERT_EQ(this->GetShape(0, 2), 1);
    ASSERT_EQ(this->GetShape(2, 1), 2);
    ASSERT_EQ(this->GetShape(1, 0), 3);
    ASSERT_EQ(this->GetShape(3, 3), 0);
}

TEST_F(TetriminoTest, Rotation90Corner)
{
    this->SetRotation(1);
    ASSERT_EQ(this->GetTopBlock(), 0);
    ASSERT_EQ(this->GetLeftBlock(), 0);
    ASSERT_EQ(this->GetBottomBlock(), 2);
    ASSERT_EQ(this->GetRightBlock(), 2);
}

TEST_F(TetriminoTest, Rotation180Shape)
{
    this->SetRotation(2);
    ASSERT_EQ(this->GetShape(0, 0), 0);
    ASSERT_EQ(this->GetShape(2, 3), 1);
    ASSERT_EQ(this->GetShape(1, 1), 2);
    ASSERT_EQ(this->GetShape(0, 2), 3);
    ASSERT_EQ(this->GetShape(1, 0), 0);
}

TEST_F(TetriminoTest, Rotation180Corner)
{
    this->SetRotation(2);
    ASSERT_EQ(this->GetTopBlock(), 0);
    ASSERT_EQ(this->GetLeftBlock(), 1);
    ASSERT_EQ(this->GetBottomBlock(), 2);
    ASSERT_EQ(this->GetRightBlock(), 3);
}

TEST_F(TetriminoTest, Rotation270Shape)
{
    this->SetRotation(3);
    ASSERT_EQ(this->GetShape(0, 0), 0);
    ASSERT_EQ(this->GetShape(3, 1), 1);
    ASSERT_EQ(this->GetShape(1, 2), 2);
    ASSERT_EQ(this->GetShape(2, 3), 3);
    ASSERT_EQ(this->GetShape(1, 0), 0);
}

TEST_F(TetriminoTest, Rotation270Corner)
{
    this->SetRotation(3);
    ASSERT_EQ(this->GetTopBlock(), 1);
    ASSERT_EQ(this->GetLeftBlock(), 1);
    ASSERT_EQ(this->GetBottomBlock(), 3);
    ASSERT_EQ(this->GetRightBlock(), 3);
}