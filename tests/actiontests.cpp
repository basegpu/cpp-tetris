#include <gtest/gtest.h>
#include "tetrimino.hpp"
#include "actions.hpp"
#include "board.hpp"
#include <numeric>


class ActionsTest :
    public ::testing::Test
{
protected:

    Tetrimino t;

    // void SetUp() override {}
    // void TearDown() override {}
    // 
    void Init(const Tetrimino::Type& type)
    {
        this->t = Tetrimino::Make(type, 0);
    }

    void Check(const std::vector<int>& widths)
    {
        int nActions = widths.size() * (Board::Width + 1)
                        - std::accumulate(widths.begin(), widths.end(), 0);
        Actions a;
        for (int ii = 0; ii < widths.size(); ii++)
        {
            a = Actions::CreateFor(this->t, {0, (int)Board::Width/2-1});
            ASSERT_EQ(a.size(), nActions);
            this->t.Rotate();
        }
    }
};

TEST_F(ActionsTest, SquareActions)
{
    this->Init(Tetrimino::Type::Square);
    this->Check({2});
}

TEST_F(ActionsTest, LineActions)
{
    this->Init(Tetrimino::Type::Line);
    this->Check({1, 4});
}

TEST_F(ActionsTest, RightHookActions)
{
    this->Init(Tetrimino::Type::RightHook);
    this->Check({2, 3, 2, 3});
}

TEST_F(ActionsTest, LeftHookActions)
{
    this->Init(Tetrimino::Type::LeftHook);
    this->Check({2, 3, 2, 3});
}

TEST_F(ActionsTest, TeeActions)
{
    this->Init(Tetrimino::Type::Tee);
    this->Check({3, 2, 3, 2});
}

TEST_F(ActionsTest, RightChairActions)
{
    this->Init(Tetrimino::Type::RightChair);
    this->Check({3, 2});
}

TEST_F(ActionsTest, LeftChairActions)
{
    this->Init(Tetrimino::Type::LeftChair);
    this->Check({3, 2});
}