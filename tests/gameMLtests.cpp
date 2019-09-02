#include <gtest/gtest.h>
#include "tetrimino.hpp"
#include "gameML.hpp"

class GameMLTest :
    public ::testing::Test,
    public GameML
{
public:
    GameMLTest() :
        GameML(false)
    {}
protected:
    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(GameMLTest, SameState)
{
    Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Square, 0);
    size_t hash_ref = t->GetHash();
    this->GetActions(t);
    ASSERT_EQ(t->GetHash(), hash_ref);
    delete t;
}

TEST_F(GameMLTest, ActionGeneration)
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