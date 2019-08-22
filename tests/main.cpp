#include "gtest/gtest.h"
#include "tetriminotests.hpp"
#include "tetriminofactorytests.hpp"

int main(int argc, char **argv)
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}