#include <gtest/gtest.h>
#include "tetrimino.hpp"


class TetriminoFactoryTest : public ::testing::Test
{
protected:
	// void SetUp() override {}
	// void TearDown() override {}
};

TEST_F(TetriminoFactoryTest, SquareShape)
{
	Tetrimino* square = Tetrimino::Make(Tetrimino::Type::Square, 0);
	ASSERT_EQ(square->GetShape(2, 2), 1);
	square->Rotate();
	ASSERT_EQ(square->GetShape(2, 1), 1);
	square->Rotate();
	ASSERT_EQ(square->GetShape(1, 1), 1);
	square->Rotate();
	ASSERT_EQ(square->GetShape(1, 2), 1);
	delete square;
}

TEST_F(TetriminoFactoryTest, SquareTopLeft)
{
	Tetrimino* square = Tetrimino::Make(Tetrimino::Type::Square, 0);
	ASSERT_EQ(square->GetTopBlock(), 1);
	ASSERT_EQ(square->GetLeftBlock(), 1);
	square->Rotate();
	ASSERT_EQ(square->GetTopBlock(), 1);
	ASSERT_EQ(square->GetLeftBlock(), 1);
	square->Rotate();
	ASSERT_EQ(square->GetTopBlock(), 1);
	ASSERT_EQ(square->GetLeftBlock(), 1);
	square->Rotate();
	ASSERT_EQ(square->GetTopBlock(), 1);
	ASSERT_EQ(square->GetLeftBlock(), 1);
	delete square;
}

TEST_F(TetriminoFactoryTest, LinePosition)
{
	Tetrimino* line = Tetrimino::Make(Tetrimino::Type::Line, 0);
	ASSERT_EQ(line->GetShape(2, 2), 1);
	line->Rotate();
	ASSERT_EQ(line->GetShape(2, 1), 1);
	line->Rotate();
	ASSERT_EQ(line->GetShape(3, 1), 1);
	line->Rotate();
	ASSERT_EQ(line->GetShape(1, 0), 1);
	delete line;
}

TEST_F(TetriminoFactoryTest, LineTopLeft)
{
	Tetrimino* line = Tetrimino::Make(Tetrimino::Type::Line, 0);
	ASSERT_EQ(line->GetTopBlock(), 0);
	ASSERT_EQ(line->GetLeftBlock(), 2);
	line->Rotate();
	ASSERT_EQ(line->GetTopBlock(), 2);
	ASSERT_EQ(line->GetLeftBlock(), 0);
	line->Rotate();
	ASSERT_EQ(line->GetTopBlock(), 0);
	ASSERT_EQ(line->GetLeftBlock(), 1);
	line->Rotate();
	ASSERT_EQ(line->GetTopBlock(), 1);
	ASSERT_EQ(line->GetLeftBlock(), 0);
	delete line;
}

TEST_F(TetriminoFactoryTest, RightHookShape)
{
	Tetrimino* rHook = Tetrimino::Make(Tetrimino::Type::RightHook, 0);
	ASSERT_EQ(rHook->GetShape(0, 1), 1);
	rHook->Rotate();
	ASSERT_EQ(rHook->GetShape(1, 2), 1);
	rHook->Rotate();
	ASSERT_EQ(rHook->GetShape(1, 2), 1);
	rHook->Rotate();
	ASSERT_EQ(rHook->GetShape(1, 2), 1);
	delete rHook;
}

TEST_F(TetriminoFactoryTest, RightHookTopLeft)
{
	Tetrimino* rHook = Tetrimino::Make(Tetrimino::Type::RightHook, 0);
	ASSERT_EQ(rHook->GetTopBlock(), 0);
	ASSERT_EQ(rHook->GetLeftBlock(), 1);
	rHook->Rotate();
	ASSERT_EQ(rHook->GetTopBlock(), 1);
	ASSERT_EQ(rHook->GetLeftBlock(), 1);
	rHook->Rotate();
	ASSERT_EQ(rHook->GetTopBlock(), 1);
	ASSERT_EQ(rHook->GetLeftBlock(), 1);
	rHook->Rotate();
	ASSERT_EQ(rHook->GetTopBlock(), 1);
	ASSERT_EQ(rHook->GetLeftBlock(), 0);
	delete rHook;
}

TEST_F(TetriminoFactoryTest, LeftHookShape)
{
	Tetrimino* lHook = Tetrimino::Make(Tetrimino::Type::LeftHook, 0);
	ASSERT_EQ(lHook->GetShape(0, 2), 1);
	lHook->Rotate();
	ASSERT_EQ(lHook->GetShape(2, 2), 1);
	lHook->Rotate();
	ASSERT_EQ(lHook->GetShape(1, 1), 1);
	lHook->Rotate();
	ASSERT_EQ(lHook->GetShape(2, 2), 1);
	delete lHook;
}

TEST_F(TetriminoFactoryTest, LeftHookTopLeft)
{
	Tetrimino* lHook = Tetrimino::Make(Tetrimino::Type::LeftHook, 0);
	ASSERT_EQ(lHook->GetTopBlock(), 0);
	ASSERT_EQ(lHook->GetLeftBlock(), 1);
	lHook->Rotate();
	ASSERT_EQ(lHook->GetTopBlock(), 1);
	ASSERT_EQ(lHook->GetLeftBlock(), 1);
	lHook->Rotate();
	ASSERT_EQ(lHook->GetTopBlock(), 1);
	ASSERT_EQ(lHook->GetLeftBlock(), 1);
	lHook->Rotate();
	ASSERT_EQ(lHook->GetTopBlock(), 1);
	ASSERT_EQ(lHook->GetLeftBlock(), 0);
	delete lHook;
}

TEST_F(TetriminoFactoryTest, TeeShape)
{
	Tetrimino* tee = Tetrimino::Make(Tetrimino::Type::Tee, 0);
	ASSERT_EQ(tee->GetShape(1, 2), 1);
	tee->Rotate();
	ASSERT_EQ(tee->GetShape(1, 1), 1);
	tee->Rotate();
	ASSERT_EQ(tee->GetShape(1, 1), 1);
	tee->Rotate();
	ASSERT_EQ(tee->GetShape(0, 2), 1);
	delete tee;
}

TEST_F(TetriminoFactoryTest, TeeTopLeft)
{
	Tetrimino* tee = Tetrimino::Make(Tetrimino::Type::Tee, 0);
	ASSERT_EQ(tee->GetTopBlock(), 1);
	ASSERT_EQ(tee->GetLeftBlock(), 1);
	tee->Rotate();
	ASSERT_EQ(tee->GetTopBlock(), 1);
	ASSERT_EQ(tee->GetLeftBlock(), 1);
	tee->Rotate();
	ASSERT_EQ(tee->GetTopBlock(), 1);
	ASSERT_EQ(tee->GetLeftBlock(), 0);
	tee->Rotate();
	ASSERT_EQ(tee->GetTopBlock(), 0);
	ASSERT_EQ(tee->GetLeftBlock(), 1);
	delete tee;
}

TEST_F(TetriminoFactoryTest, RightChairShape)
{
	Tetrimino* rChair = Tetrimino::Make(Tetrimino::Type::RightChair, 0);
	ASSERT_EQ(rChair->GetShape(1, 1), 1);
	rChair->Rotate();
	ASSERT_EQ(rChair->GetShape(2, 2), 1);
	rChair->Rotate();
	ASSERT_EQ(rChair->GetShape(1, 1), 1);
	rChair->Rotate();
	ASSERT_EQ(rChair->GetShape(0, 2), 1);
	delete rChair;
}

TEST_F(TetriminoFactoryTest, RightChairTopLeft)
{
	Tetrimino* rChair = Tetrimino::Make(Tetrimino::Type::RightChair, 0);
	ASSERT_EQ(rChair->GetTopBlock(), 1);
	ASSERT_EQ(rChair->GetLeftBlock(), 1);
	rChair->Rotate();
	ASSERT_EQ(rChair->GetTopBlock(), 1);
	ASSERT_EQ(rChair->GetLeftBlock(), 1);
	rChair->Rotate();
	ASSERT_EQ(rChair->GetTopBlock(), 1);
	ASSERT_EQ(rChair->GetLeftBlock(), 0);
	rChair->Rotate();
	ASSERT_EQ(rChair->GetTopBlock(), 0);
	ASSERT_EQ(rChair->GetLeftBlock(), 1);
	delete rChair;
}

TEST_F(TetriminoFactoryTest, LeftChairShape)
{
	Tetrimino* lChair = Tetrimino::Make(Tetrimino::Type::LeftChair, 0);
	ASSERT_EQ(lChair->GetShape(2, 0), 1);
	lChair->Rotate();
	ASSERT_EQ(lChair->GetShape(1, 1), 1);
	lChair->Rotate();
	ASSERT_EQ(lChair->GetShape(2, 2), 1);
	lChair->Rotate();
	ASSERT_EQ(lChair->GetShape(2, 1), 1);
	delete lChair;
}

TEST_F(TetriminoFactoryTest, LeftChairTopLeft)
{
	Tetrimino* lChair = Tetrimino::Make(Tetrimino::Type::LeftChair, 0);
	ASSERT_EQ(lChair->GetTopBlock(), 1);
	ASSERT_EQ(lChair->GetLeftBlock(), 0);
	lChair->Rotate();
	ASSERT_EQ(lChair->GetTopBlock(), 0);
	ASSERT_EQ(lChair->GetLeftBlock(), 1);
	lChair->Rotate();
	ASSERT_EQ(lChair->GetTopBlock(), 1);
	ASSERT_EQ(lChair->GetLeftBlock(), 1);
	lChair->Rotate();
	ASSERT_EQ(lChair->GetTopBlock(), 1);
	ASSERT_EQ(lChair->GetLeftBlock(), 1);
	delete lChair;
}