#include <gtest/gtest.h>
#include "monitor.hpp"
#include <exception>

void CheckStats(const Monitor::Stats& stats, const std::vector<double>& ref)
{
    ASSERT_EQ(stats.size(), ref.size());
    for (int ii = 0; ii < ref.size(); ii++)
    {
        ASSERT_NEAR(
            stats.at(static_cast<Monitor::Statistics>(ii)),
            ref.at(ii),
            fabs(ref.at(ii))*1e-6);   
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

TEST(MonitorTest, TwoDataPoint)
{
    Monitor m;
    m.AddOutput(10, 1.0);
    m.AddOutput(5, 2.0);
    CheckStats(m.GetScoreStatistics(), {5, 10, 7.5, 7.5, 12.5});
    CheckStats(m.GetTimeStatistics(), {1.0, 2.0, 1.5, 1.5, 0.5});
}

TEST(MonitorTest, ThreeDataPoint)
{
    Monitor m;
    m.AddOutput(10, 1.0);
    m.AddOutput(5, 2.0);
    m.AddOutput(9, 4.5);
    CheckStats(m.GetScoreStatistics(), {5, 10, 9, 8, 7.0, -0.9719086});
    CheckStats(m.GetTimeStatistics(), {1.0, 4.5, 2.0, 2.5, 3.25, 0.768046});
}