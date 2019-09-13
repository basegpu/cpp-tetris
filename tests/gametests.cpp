#include <gtest/gtest.h>
#include <vector>
#include "game.hpp"


class GameTest : public ::testing::Test, public Game
{
protected:
    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(GameTest, Reset)
{
    SetRandom(true);
    this->state.MakeMove(Moves::Advance);
    ASSERT_TRUE(this->state.GetBoard().CountFilledBlocks() > 0);
    this->Reset();
    ASSERT_EQ(this->state.GetBoard().CountFilledBlocks(), 0);
}

TEST_F(GameTest, PlaySequence)
{
    if (Board::Width == 10)
    {
        SetRandom(false);
        Game game;
        ASSERT_EQ(game.GetScore(), 0);
        // moves represented by console input:
        // jjjjmillllmlmiijmijjjjjmimlmlmijmiillllmiiilllmijjjm
        std::vector<Moves> moves = {
            Moves::Left,
            Moves::Left,
            Moves::Left,
            Moves::Left,
            Moves::Advance,
            Moves::Rotate,
            Moves::Right,
            Moves::Right,
            Moves::Right,
            Moves::Right,
            Moves::Advance,
            Moves::Right,
            Moves::Advance,
            Moves::Rotate,
            Moves::Rotate,
            Moves::Left,
            Moves::Advance,
            Moves::Rotate,
            Moves::Left,
            Moves::Left,
            Moves::Left,
            Moves::Left,
            Moves::Left,
            Moves::Advance,
            Moves::Rotate,
            Moves::Advance,
            Moves::Right,
            Moves::Advance,
            Moves::Right,
            Moves::Advance,
            Moves::Rotate,
            Moves::Left,
            Moves::Advance,
            Moves::Rotate,
            Moves::Rotate,
            Moves::Right,
            Moves::Right,
            Moves::Right,
            Moves::Right,
            Moves::Advance,
            Moves::Rotate,
            Moves::Rotate,
            Moves::Rotate,
            Moves::Right,
            Moves::Right,
            Moves::Right,
            Moves::Advance,
            Moves::Rotate,
            Moves::Left,
            Moves::Left,
            Moves::Left,
            Moves::Advance
        };
        game.PlaySequence(moves);
        ASSERT_EQ(game.GetScore(), 2);
    }
    else
    {
        FAIL() << "This test passes only for board width = 10, not for " << Board::Width << ".";
    }
}

