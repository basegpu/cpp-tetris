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

TEST_F(GameMLTest, NoActions)
{
	Tetrimino* t = Tetrimino::Make(Tetrimino::Type::Square, 0);
	ASSERT_EQ(this->GetScore(), 0);
	ASSERT_EQ(this->GetActions(t).size(), 0);
}
