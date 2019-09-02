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

TEST_F(GameMLTest, SquareActions)
{
	Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Square, 0);
	Actions a = this->GetActions(t);
	ASSERT_EQ(a.size(), 9);
	delete t;
}

TEST_F(GameMLTest, LineActions)
{
	Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Line, 0);
	Actions a = this->GetActions(t);
	ASSERT_EQ(a.size(), 10+7);
	delete t;
}