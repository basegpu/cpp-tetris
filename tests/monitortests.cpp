#include <gtest/gtest.h>
#include "monitor.hpp"
#include <exception>


class MonitorTest :
    public ::testing::Test, public Monitor
{
protected:

    // void SetUp() override {}
    // void TearDown() override {}
};

TEST_F(MonitorTest, NoData)
{
    ASSERT_THROW(this->GetScoreStatistics(), std::logic_error);
    ASSERT_THROW(this->GetTimeStatistics(), std::logic_error);
}