#include <gtest/gtest.h>
#include <algorithm>
#include "board.hpp"
#include "tetrimino.hpp"


class BoardTest : public ::testing::Test, public Board
{
protected:
    void SetUp() override
    {
        square = Tetrimino::Make(Tetrimino::Type::Square, 0);
        line0 = Tetrimino::Make(Tetrimino::Type::Line, 0);
        line90 = Tetrimino::Make(Tetrimino::Type::Line, 1);
        line270 = Tetrimino::Make(Tetrimino::Type::Line, 3);
        lHook180 = Tetrimino::Make(Tetrimino::Type::LeftHook, 2);
        tee180 = Tetrimino::Make(Tetrimino::Type::Tee, 2);
    }
    // void TearDown() override {}
    Tetrimino square, line0, line90, line270, lHook180, tee180;
};

TEST_F(BoardTest, EmptyBoard)
{
    this->Reset();
    for (int ii = 0; ii < Board::Width; ii++)
    {
        for (int jj = 0; jj < Board::Height; jj++)
        {
            ASSERT_EQ(this->IsFreeBlock(ii, jj), true);
        }
    }
}

TEST_F(BoardTest, BadBlockAccess)
{
    ASSERT_THROW(this->IsFreeBlock(100, 100), std::out_of_range);
}

TEST_F(BoardTest, SingleTetrimino)
{
    this->Reset();
    this->AddTetrimino(this->square, 0, 0);
    ASSERT_EQ(this->IsFreeBlock(0, 0), true);
    ASSERT_EQ(this->IsFreeBlock(1, 1), false);
    ASSERT_EQ(this->IsFreeBlock(2, 2), false);
    ASSERT_EQ(this->IsFreeBlock(3, 3), true);
}

TEST_F(BoardTest, TetriminoOutside)
{
    ASSERT_THROW(
        this->AddTetrimino(
            this->line90,
            Board::Width-Tetrimino::BlocksPerPiece+1, 0),
        std::out_of_range);
    ASSERT_THROW(
        this->AddTetrimino(
            this->line270,
            0, 100),
        std::out_of_range);
}

TEST_F(BoardTest, DeleteSingleLine)
{
    this->Reset();
    this->AddTetrimino(this->line90, 0, 0);
    ASSERT_EQ(this->IsFreeBlock(0, 3), true);
    this->DeleteLine(10);
    ASSERT_EQ(this->IsFreeBlock(0, 3), false);
}

TEST_F(BoardTest, DeleteLineOutisde)
{
    ASSERT_THROW(this->DeleteLine(Board::Height), std::out_of_range);
}

TEST_F(BoardTest, GameOver)
{
    this->Reset();
    this->AddTetrimino(this->line90, 0, 0);
    ASSERT_EQ(this->IsGameOver(), false);
    this->AddTetrimino(this->line0, 5, 0);
    ASSERT_EQ(this->IsGameOver(), true);
}

TEST_F(BoardTest, InitStats)
{
    this->Reset();
    ASSERT_EQ(this->GetHoles(), 0);
    ASSERT_EQ(this->GetMaxLevel(), 0);
    ASSERT_EQ(this->GetMinMaxLevel(), 0);
}

TEST_F(BoardTest, SingleHoles)
{
    this->Reset();
    this->AddTetrimino(this->tee180, 0, Board::Height - 3);
    //TETRIS_MESSAGE(this->Print());
    this->CalcStatistics();
    ASSERT_EQ(this->GetHoles(), 2);
}

TEST_F(BoardTest, MultipleHole)
{
    this->Reset();
    this->AddTetrimino(this->line0, -2, Board::Height - 4);
    this->AddTetrimino(this->line0, 1, Board::Height - 4);
    this->AddTetrimino(this->line90, 0, 13);
    this->CalcStatistics();
    ASSERT_EQ(this->CountFilledBlocks(), 12);
    ASSERT_EQ(this->GetHoles(), 8);
}

TEST_F(BoardTest, ManyHoles)
{
    this->Reset();
    this->AddTetrimino(this->lHook180, Board::Width - 3, Board::Height - 4);
    this->AddTetrimino(this->lHook180, Board::Width - 3, Board::Height - 7);
    //TETRIS_MESSAGE(this->Print());
    this->CalcStatistics();
    ASSERT_EQ(this->GetHoles(), 4);
}

TEST_F(BoardTest, MaxLevel)
{
    this->Reset();
    this->AddTetrimino(this->line90, 0, Board::Height - 3);
    this->CalcStatistics();
    ASSERT_EQ(this->GetMaxLevel(), 1);
    this->AddTetrimino(this->line0, 0, Board::Height - 5);
    this->CalcStatistics();
    ASSERT_EQ(this->GetMaxLevel(), 5);
}

TEST_F(BoardTest, MinMaxLevelSimple)
{
    this->Reset();
    this->AddTetrimino(this->line0, -2, Board::Height - 4);
    this->CalcStatistics();
    ASSERT_EQ(this->GetMinMaxLevel(), 4);
    this->AddTetrimino(this->line90, Board::Width - 4, Board::Height - 3);
    this->CalcStatistics();
    ASSERT_EQ(this->GetMinMaxLevel(), 4);
}

TEST_F(BoardTest, MinMaxLevel)
{
    if (Board::Width == 10)
    {
        this->Reset();
        this->AddTetrimino(this->line0, -2, Board::Height - 4);
        this->AddTetrimino(this->line0, -1, Board::Height - 4);
        this->AddTetrimino(this->line90, Board::Width - 4, Board::Height - 3);
        this->AddTetrimino(this->line90, 2, Board::Height - 5);
        this->CalcStatistics();
        //TETRIS_MESSAGE(this->Print());
        ASSERT_EQ(this->GetMinMaxLevel(), 3);
    }
    else
    {
        FAIL() << "This test passes only for board width = 10, not for " << Board::Width << ".";
    }
}

TEST_F(BoardTest, DeletePossibleLines)
{
    if (Board::Width == 10)
    {
        this->Reset();
        this->AddTetrimino(this->line90, 0, Board::Height - 3);
        this->AddTetrimino(this->line90, 4, Board::Height - 3);
        this->AddTetrimino(this->line0, 6, Board::Height - 4);
        this->AddTetrimino(this->line0, 7, Board::Height - 4);
        ASSERT_EQ(this->CountFilledBlocks(), Board::Height - 4);
        this->DeletePossibleLines();
        ASSERT_EQ(this->CountFilledBlocks(), 6);
    }
    else
    {
        FAIL() << "This test passes only for board width = 10, not for " << Board::Width << ".";
    }
}

TEST_F(BoardTest, PossibleMoves)
{
    if (Board::Width == 10)
    {
        this->Reset();
        this->AddTetrimino(this->line90, 0, Board::Height - 3);
        this->AddTetrimino(this->line90, 4, Board::Height - 3);
        this->AddTetrimino(this->line90, 4, Board::Height - 4);
        this->AddTetrimino(this->line0, 6, Board::Height - 4);
        this->AddTetrimino(this->line0, 7, Board::Height - 4);
        ASSERT_EQ(this->IsPossibleMove(this->square, 4, 4), true);
        ASSERT_EQ(this->IsPossibleMove(this->square, 7, Board::Height - 7), true);
        ASSERT_EQ(this->IsPossibleMove(this->square, 8, Board::Height - 7), false);
        ASSERT_EQ(this->IsPossibleMove(this->square, 7, Board::Height - 6), false);
        ASSERT_EQ(this->IsPossibleMove(this->lHook180, 6, Board::Height - 6), true);
    }
    else
    {
        FAIL() << "This test passes only for board width = 10, not for " << Board::Width << ".";
    }
}

TEST(MiscBoardTest, Copy)
{
    Tetrimino line90 = Tetrimino::Make(Tetrimino::Type::Line, 1);
    Board board;
    Board copy = board;
    copy.AddTetrimino(line90, 0, Board::Height - 3);
    ASSERT_EQ(copy.CountFilledBlocks(), 4);
    ASSERT_EQ(board.CountFilledBlocks(), 0);
}
