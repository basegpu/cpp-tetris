#include <gtest/gtest.h>
#include "tetrimino.hpp"

template<int N>
size_t bitstring2ullong(const std::string& bits)
{
    return std::bitset<N>(bits).to_ullong();
}

TEST(TetriminoFactoryTest, SquareProps)
{
    Tetrimino square = Tetrimino::Make(Tetrimino::Type::Square, 0);
    ASSERT_EQ(square.GetSymmetry(), Tetrimino::Symmetry::Point);
    ASSERT_EQ(square.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000000011001100000"));
}

TEST(TetriminoFactoryTest, SquareShape)
{
    Tetrimino square = Tetrimino::Make(Tetrimino::Type::Square, 0);
    ASSERT_EQ(square.GetShape(2, 2), 1);
    square.Rotate();
    ASSERT_EQ(square.GetShape(2, 1), 1);
    square.Rotate();
    ASSERT_EQ(square.GetShape(1, 1), 1);
    square.Rotate();
    ASSERT_EQ(square.GetShape(1, 2), 1);
}

TEST(TetriminoFactoryTest, SquareTopLeft)
{
    Tetrimino square = Tetrimino::Make(Tetrimino::Type::Square, 0);
    ASSERT_EQ(square.GetTopBlock(), 1);
    ASSERT_EQ(square.GetLeftBlock(), 1);
    square.Rotate();
    ASSERT_EQ(square.GetTopBlock(), 1);
    ASSERT_EQ(square.GetLeftBlock(), 1);
    square.Rotate();
    ASSERT_EQ(square.GetTopBlock(), 1);
    ASSERT_EQ(square.GetLeftBlock(), 1);
    square.Rotate();
    ASSERT_EQ(square.GetTopBlock(), 1);
    ASSERT_EQ(square.GetLeftBlock(), 1);
}

TEST(TetriminoFactoryTest, LineProps)
{
    Tetrimino line = Tetrimino::Make(Tetrimino::Type::Line, 0);
    ASSERT_EQ(line.GetSymmetry(), Tetrimino::Symmetry::Line);
    ASSERT_EQ(line.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000100010001000100"));
}

TEST(TetriminoFactoryTest, LineShape)
{
    Tetrimino line = Tetrimino::Make(Tetrimino::Type::Line, 0);
    ASSERT_EQ(line.GetShape(2, 2), 1);
    line.Rotate();
    ASSERT_EQ(line.GetShape(2, 1), 1);
    line.Rotate();
    ASSERT_EQ(line.GetShape(3, 1), 1);
    line.Rotate();
    ASSERT_EQ(line.GetShape(1, 0), 1);
}

TEST(TetriminoFactoryTest, LineTopLeft)
{
    Tetrimino line = Tetrimino::Make(Tetrimino::Type::Line, 0);
    ASSERT_EQ(line.GetTopBlock(), 0);
    ASSERT_EQ(line.GetLeftBlock(), 2);
    line.Rotate();
    ASSERT_EQ(line.GetTopBlock(), 2);
    ASSERT_EQ(line.GetLeftBlock(), 0);
    line.Rotate();
    ASSERT_EQ(line.GetTopBlock(), 0);
    ASSERT_EQ(line.GetLeftBlock(), 1);
    line.Rotate();
    ASSERT_EQ(line.GetTopBlock(), 1);
    ASSERT_EQ(line.GetLeftBlock(), 0);
}

TEST(TetriminoFactoryTest, RightHookProps)
{
    Tetrimino rHook = Tetrimino::Make(Tetrimino::Type::RightHook, 0);
    ASSERT_EQ(rHook.GetSymmetry(), Tetrimino::Symmetry::None);
    ASSERT_EQ(rHook.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000000011000100010"));
}

TEST(TetriminoFactoryTest, RightHookShape)
{
    Tetrimino rHook = Tetrimino::Make(Tetrimino::Type::RightHook, 0);
    ASSERT_EQ(rHook.GetShape(0, 1), 1);
    rHook.Rotate();
    ASSERT_EQ(rHook.GetShape(1, 2), 1);
    rHook.Rotate();
    ASSERT_EQ(rHook.GetShape(1, 2), 1);
    rHook.Rotate();
    ASSERT_EQ(rHook.GetShape(1, 2), 1);
}

TEST(TetriminoFactoryTest, RightHookTopLeft)
{
    Tetrimino rHook = Tetrimino::Make(Tetrimino::Type::RightHook, 0);
    ASSERT_EQ(rHook.GetTopBlock(), 0);
    ASSERT_EQ(rHook.GetLeftBlock(), 1);
    rHook.Rotate();
    ASSERT_EQ(rHook.GetTopBlock(), 1);
    ASSERT_EQ(rHook.GetLeftBlock(), 1);
    rHook.Rotate();
    ASSERT_EQ(rHook.GetTopBlock(), 1);
    ASSERT_EQ(rHook.GetLeftBlock(), 1);
    rHook.Rotate();
    ASSERT_EQ(rHook.GetTopBlock(), 1);
    ASSERT_EQ(rHook.GetLeftBlock(), 0);
}

TEST(TetriminoFactoryTest, LeftHookProps)
{
    Tetrimino lHook = Tetrimino::Make(Tetrimino::Type::LeftHook, 0);
    ASSERT_EQ(lHook.GetSymmetry(), Tetrimino::Symmetry::None);
    ASSERT_EQ(lHook.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000000011001000100"));
}

TEST(TetriminoFactoryTest, LeftHookShape)
{
    Tetrimino lHook = Tetrimino::Make(Tetrimino::Type::LeftHook, 0);
    ASSERT_EQ(lHook.GetShape(0, 2), 1);
    lHook.Rotate();
    ASSERT_EQ(lHook.GetShape(2, 2), 1);
    lHook.Rotate();
    ASSERT_EQ(lHook.GetShape(1, 1), 1);
    lHook.Rotate();
    ASSERT_EQ(lHook.GetShape(2, 2), 1);
}

TEST(TetriminoFactoryTest, LeftHookTopLeft)
{
    Tetrimino lHook = Tetrimino::Make(Tetrimino::Type::LeftHook, 0);
    ASSERT_EQ(lHook.GetTopBlock(), 0);
    ASSERT_EQ(lHook.GetLeftBlock(), 1);
    lHook.Rotate();
    ASSERT_EQ(lHook.GetTopBlock(), 1);
    ASSERT_EQ(lHook.GetLeftBlock(), 1);
    lHook.Rotate();
    ASSERT_EQ(lHook.GetTopBlock(), 1);
    ASSERT_EQ(lHook.GetLeftBlock(), 1);
    lHook.Rotate();
    ASSERT_EQ(lHook.GetTopBlock(), 1);
    ASSERT_EQ(lHook.GetLeftBlock(), 0);
}

TEST(TetriminoFactoryTest, TeeProps)
{
    Tetrimino tee = Tetrimino::Make(Tetrimino::Type::Tee, 0);
    ASSERT_EQ(tee.GetSymmetry(), Tetrimino::Symmetry::None);
    ASSERT_EQ(tee.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000000111001000000"));
}

TEST(TetriminoFactoryTest, TeeShape)
{
    Tetrimino tee = Tetrimino::Make(Tetrimino::Type::Tee, 0);
    ASSERT_EQ(tee.GetShape(1, 2), 1);
    tee.Rotate();
    ASSERT_EQ(tee.GetShape(1, 1), 1);
    tee.Rotate();
    ASSERT_EQ(tee.GetShape(1, 1), 1);
    tee.Rotate();
    ASSERT_EQ(tee.GetShape(0, 2), 1);
}

TEST(TetriminoFactoryTest, TeeTopLeft)
{
    Tetrimino tee = Tetrimino::Make(Tetrimino::Type::Tee, 0);
    ASSERT_EQ(tee.GetTopBlock(), 1);
    ASSERT_EQ(tee.GetLeftBlock(), 1);
    tee.Rotate();
    ASSERT_EQ(tee.GetTopBlock(), 1);
    ASSERT_EQ(tee.GetLeftBlock(), 1);
    tee.Rotate();
    ASSERT_EQ(tee.GetTopBlock(), 1);
    ASSERT_EQ(tee.GetLeftBlock(), 0);
    tee.Rotate();
    ASSERT_EQ(tee.GetTopBlock(), 0);
    ASSERT_EQ(tee.GetLeftBlock(), 1);
}

TEST(TetriminoFactoryTest, RightChairProps)
{
    Tetrimino rChair = Tetrimino::Make(Tetrimino::Type::RightChair, 0);
    ASSERT_EQ(rChair.GetSymmetry(), Tetrimino::Symmetry::Line);
    ASSERT_EQ(rChair.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000000110001100000"));
}

TEST(TetriminoFactoryTest, RightChairShape)
{
    Tetrimino rChair = Tetrimino::Make(Tetrimino::Type::RightChair, 0);
    ASSERT_EQ(rChair.GetShape(1, 1), 1);
    rChair.Rotate();
    ASSERT_EQ(rChair.GetShape(2, 2), 1);
    rChair.Rotate();
    ASSERT_EQ(rChair.GetShape(1, 1), 1);
    rChair.Rotate();
    ASSERT_EQ(rChair.GetShape(0, 2), 1);
}

TEST(TetriminoFactoryTest, RightChairTopLeft)
{
    Tetrimino rChair = Tetrimino::Make(Tetrimino::Type::RightChair, 0);
    ASSERT_EQ(rChair.GetTopBlock(), 1);
    ASSERT_EQ(rChair.GetLeftBlock(), 1);
    rChair.Rotate();
    ASSERT_EQ(rChair.GetTopBlock(), 1);
    ASSERT_EQ(rChair.GetLeftBlock(), 1);
    rChair.Rotate();
    ASSERT_EQ(rChair.GetTopBlock(), 1);
    ASSERT_EQ(rChair.GetLeftBlock(), 0);
    rChair.Rotate();
    ASSERT_EQ(rChair.GetTopBlock(), 0);
    ASSERT_EQ(rChair.GetLeftBlock(), 1);
}

TEST(TetriminoFactoryTest, LeftChairProps)
{
    Tetrimino lChair = Tetrimino::Make(Tetrimino::Type::LeftChair, 0);
    ASSERT_EQ(lChair.GetSymmetry(), Tetrimino::Symmetry::Line);
    ASSERT_EQ(lChair.GetHash(), bitstring2ullong<TETRIMINO_HASHSIZE>("000000001101100000"));
}

TEST(TetriminoFactoryTest, LeftChairShape)
{
    Tetrimino lChair = Tetrimino::Make(Tetrimino::Type::LeftChair, 0);
    ASSERT_EQ(lChair.GetShape(2, 0), 1);
    lChair.Rotate();
    ASSERT_EQ(lChair.GetShape(1, 1), 1);
    lChair.Rotate();
    ASSERT_EQ(lChair.GetShape(2, 2), 1);
    lChair.Rotate();
    ASSERT_EQ(lChair.GetShape(2, 1), 1);
}

TEST(TetriminoFactoryTest, LeftChairTopLeft)
{
    Tetrimino lChair = Tetrimino::Make(Tetrimino::Type::LeftChair, 0);
    ASSERT_EQ(lChair.GetTopBlock(), 1);
    ASSERT_EQ(lChair.GetLeftBlock(), 0);
    lChair.Rotate();
    ASSERT_EQ(lChair.GetTopBlock(), 0);
    ASSERT_EQ(lChair.GetLeftBlock(), 1);
    lChair.Rotate();
    ASSERT_EQ(lChair.GetTopBlock(), 1);
    ASSERT_EQ(lChair.GetLeftBlock(), 1);
    lChair.Rotate();
    ASSERT_EQ(lChair.GetTopBlock(), 1);
    ASSERT_EQ(lChair.GetLeftBlock(), 1);
}