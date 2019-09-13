#include "globals.hpp"
#include "monitor.hpp"
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <exception>


void Monitor::AddOutput(const int& score, const double& time)
{
    this->Scores.push_back(score);
    this->Times.push_back(time);
}

Monitor::Stats Monitor::GetScoreStatistics()
{
    return CalcStatistics(this->Scores);
}

Monitor::Stats Monitor::GetTimeStatistics()
{
    return CalcStatistics(this->Times);
}

Monitor::Stats Monitor::CalcStatistics(std::vector<double>& vec)
{
    Stats stats;
    if (vec.size() > 0)
    {
        std::sort(vec.begin(), vec.end());
        stats[Statistics::Min] = vec.front();
        stats[Statistics::Max] = vec.back();
        stats[Statistics::Median] = this->CalcMedian(vec);
        stats[Statistics::Mean] = std::accumulate(vec.begin(), vec.end(), 0.0) / vec.size();
        if (vec.size() > 1)
        {
            stats[Statistics::Variance] = this->CalcNthMoment<double, 2>(
                vec.begin(),
                vec.end(),
                stats[Statistics::Mean]);
            if (vec.size() > 2)
            {
                stats[Statistics::Skewness] = 0.0;
            }
        }
    }
    return stats;
}