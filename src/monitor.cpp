#include "globals.hpp"
#include "monitor.hpp"
#include <vector>
#include <map>
#include <numeric>
#include <algorithm>
#include <cmath>
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

void Monitor::Print()
{
    TETRIS_MESSAGE("Score Statistics")
    this->PrintStats(this->GetScoreStatistics());
    TETRIS_MESSAGE("Performance Statistics")
    this->PrintStats(this->GetTimeStatistics());
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
            stats[Statistics::Variance] = this->ComputeVariance<double>(
                vec.begin(),
                vec.end(),
                stats[Statistics::Mean]);
            if (vec.size() > 2)
            {
                stats[Statistics::Skewness] = this->ComputeSkewness<double>(
                    vec.begin(),
                    vec.end(),
                    stats[Statistics::Mean]);
            }
        }
    }
    return stats;
}

void Monitor::PrintStats(const Stats& s)
{
    TETRIS_MESSAGE("min: " << s.at(Statistics::Min) << ", max: " << s.at(Statistics::Max))
    TETRIS_MESSAGE("median: " << s.at(Statistics::Median) << ", mean: " << s.at(Statistics::Mean))
    if (s.count(Statistics::Variance))
    {
        TETRIS_MESSAGE("stdev: " << std::sqrt(s.at(Statistics::Variance)))
    }
    if (s.count(Statistics::Skewness))
    {
        TETRIS_MESSAGE("skewness: " << s.at(Statistics::Skewness))
    }
}