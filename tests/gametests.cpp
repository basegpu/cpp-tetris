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
    ASSERT_NE(this->board, nullptr);
    ASSERT_NE(this->piece, nullptr);
    ASSERT_NE(this->nextPiece, nullptr);
}

TEST_F(GameTest, NewPiece)
{
    Tetrimino* p = this->nextPiece;
    this->AddNewPiece();
    ASSERT_EQ(this->piece, p);
}


TEST_F(GameTest, SameState)
{
    Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Square, 0);
    size_t hash_ref = t->GetHash();
    this->piece = t;
    this->GetPossibleActions();
    ASSERT_EQ(t->GetHash(), hash_ref);
}
/*
TEST_F(GameTest, ActionGeneration)
{
    Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Square, 0);
    ASSERT_EQ(this->actionsRegistry.size(), 0);
    this->GetActions(t);
    ASSERT_EQ(this->actionsRegistry.size(), 1);
    this->GetActions(t);
    ASSERT_EQ(this->actionsRegistry.size(), 1);
    t->Rotate();
    this->GetActions(t);
    ASSERT_EQ(this->actionsRegistry.size(), 2);
    delete t;
}
*/

TEST(NonRandomGameTest, PlaySequence)
{
    if (Board::Width == 10)
    {
        Game* game = new Game(false);
        ASSERT_EQ(game->GetScore(), 0);
        // moves represented by console input:
        // jjjjmillllmlmiijmijjjjjmimlmlmijmiillllmiiilllmijjjm
        std::vector<Game::Moves> moves = {
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Advance,
            Game::Moves::Right,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Rotate,
            Game::Moves::Left,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Advance,
            Game::Moves::Right,
            Game::Moves::Advance,
            Game::Moves::Right,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Left,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Rotate,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Rotate,
            Game::Moves::Rotate,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Right,
            Game::Moves::Advance,
            Game::Moves::Rotate,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Left,
            Game::Moves::Advance
        };
        game->PlaySequence(moves);
        ASSERT_EQ(game->GetScore(), 2);
        delete game;
    }
    else
    {
        FAIL() << "This test passes only for board width = 10, not for " << Board::Width << ".";
    }
}

