#include <gtest/gtest.h>
#include <vector>
#include "state.hpp"


class StateTest : public ::testing::Test, public State
{
protected:
    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(StateTest, Init)
{
    ASSERT_NE(&this->GetBoard(), nullptr);
    ASSERT_NE(&this->GetPosition(), nullptr);
    ASSERT_NE(this->GetCurrentPiece(), nullptr);
    ASSERT_NE(this->GetNextPiece(), nullptr);
}

TEST_F(StateTest, NewPiece)
{
    const Tetrimino p = *this->GetNextPiece();
    this->AddNewPiece();
    ASSERT_EQ(*this->GetCurrentPiece(), p);
}

TEST_F(StateTest, CopyConstructor)
{
    this->Advance();
    State copy = static_cast<State>(*this);
    ASSERT_NE(&copy, this);
    ASSERT_NE(&copy.GetBoard(), &this->GetBoard());
    ASSERT_EQ(copy.GetBoard().CountFilledBlocks(), this->GetBoard().CountFilledBlocks());
    ASSERT_NE(copy.GetCurrentPiece(), this->GetCurrentPiece());
    ASSERT_NE(copy.GetNextPiece(), this->GetNextPiece());
    ASSERT_TRUE(*copy.GetCurrentPiece() == *this->GetCurrentPiece());
    this->Advance();
    ASSERT_NE(copy.GetBoard().CountFilledBlocks(), this->GetBoard().CountFilledBlocks());
    ASSERT_TRUE(*copy.GetNextPiece() == *this->GetCurrentPiece());
    const bool equal = this->currentPiece == this->nextPiece;
    ASSERT_TRUE(equal == (*copy.GetCurrentPiece() == *this->GetCurrentPiece()));
}

TEST_F(StateTest, NewState)
{
    this->Advance();
    ASSERT_TRUE(this->GetBoard().CountFilledBlocks() >= 4);
    State state;
    ASSERT_EQ(state.GetBoard().CountFilledBlocks(), 0);
    ASSERT_NE(this->GetCurrentPiece(), state.GetCurrentPiece());
    ASSERT_NE(state.GetCurrentPiece(), nullptr);
    ASSERT_NE(state.GetNextPiece(), nullptr);
    state.MakeMove(Moves::Advance);
    ASSERT_TRUE(state.GetBoard().CountFilledBlocks() >= 4);
}

TEST_F(StateTest, Reset)
{
    this->Advance();
    ASSERT_TRUE(this->GetBoard().CountFilledBlocks() >= 4);
    this->Reset();
    ASSERT_EQ(this->GetBoard().CountFilledBlocks(), 0);
}

