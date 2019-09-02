#include <gtest/gtest.h>
#include "tetrimino.hpp"
#include "actions.hpp"
#include "board.hpp"


TEST(ActionsTest, SquareActions)
{
    Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Square, 0);
    Actions a = Actions::CreateFor(t, {0, (int)Board::Width/2});
    ASSERT_EQ(a.size(), Board::Width - 2 + 1);
    delete t;
}

TEST(ActionsTest, LineActions)
{
    Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Line, 0);
    Actions a = Actions::CreateFor(t, {0, (int)Board::Width/2});
    int nActions = 2*Board::Width + 2 - 1 - 4;
    ASSERT_EQ(a.size(), nActions);
    t->Rotate();
    ASSERT_EQ(a.size(), nActions);
    delete t;
}