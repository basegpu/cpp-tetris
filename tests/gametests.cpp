#include <gtest/gtest.h>
#include <vector>
#include "game.hpp"


class GameTest : public ::testing::Test, public Game
{
protected:
    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(GameTest, Init)
{
    ASSERT_NE(&this->board, nullptr);
    ASSERT_NE(this->currentPiece, nullptr);
    ASSERT_NE(this->nextPiece, nullptr);
}

TEST_F(GameTest, NewPiece)
{
    Tetrimino p = *this->nextPiece;
    this->AddNewPiece();
    ASSERT_EQ(*this->currentPiece, p);
}


TEST_F(GameTest, SameState)
{
    Tetrimino t = Tetrimino::Make(Tetrimino::Type::Square, 0);
    size_t hash_ref = t.GetHash();
    *this->currentPiece = t;
    this->GetPossibleActions();
    ASSERT_EQ(t.GetHash(), hash_ref);
}

TEST_F(GameTest, ActionGeneration)
{
    Tetrimino t = Tetrimino::Make(Tetrimino::Type::Square, 0);
    ASSERT_EQ(this->actionsRegistry.size(), 0);
    *this->currentPiece = t;
    this->GetPossibleActions();
    ASSERT_EQ(this->actionsRegistry.size(), 1);
    this->GetPossibleActions();
    ASSERT_EQ(this->actionsRegistry.size(), 1);
    t.Rotate();
    *this->currentPiece = t;
    this->GetPossibleActions();
    ASSERT_EQ(this->actionsRegistry.size(), 2);
}

TEST(NonRandomGameTest, PlaySequence)
{
    if (Board::Width == 10)
    {
        Game game(false);
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

