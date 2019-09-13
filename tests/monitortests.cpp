#include <gtest/gtest.h>
#include "monitor.hpp"
#include <exception>

void CheckStats(const Monitor::Stats& stats, const std::vector<double>& ref)
{
    ASSERT_EQ(stats.size(), ref.size());
    for (int ii = 0; ii < ref.size(); ii++)
    {
        ASSERT_EQ(stats.at(static_cast<Monitor::Statistics>(ii)), ref.at(ii));   
    }
}

TEST(MonitorTest, NoData)
{
    Monitor m;
    CheckStats(m.GetScoreStatistics(), {});
    CheckStats(m.GetTimeStatistics(), {});
}

TEST(MonitorTest, OneDataPoint)
{
    Monitor m;
    m.AddOutput(10, 1.0);
    CheckStats(m.GetScoreStatistics(), {10, 10, 10, 10});
    CheckStats(m.GetTimeStatistics(), {1.0, 1.0, 1.0, 1.0});
}