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

template<typename T>
Monitor::Stats Monitor::CalcStatistics(std::vector<T>& vec)
{
    Stats stats;
    if (vec.size() > 0)
    {
        std::sort(vec.begin(), vec.end());
        stats[Statistics::Min] = vec.front();
        stats[Statistics::Max] = vec.back();
        stats[Statistics::Median] = this->CalcMedian(vec);
        stats[Statistics::Mean] = std::accumulate(vec.begin(), vec.end(), 0.0);
        if (vec.size() > 1)
        {
            stats[Statistics::Variance] = 0.0;
            if (vec.size() > 2)
            {
                stats[Statistics::Skewness] = 0.0;
            }
        }
    }
    return stats;
}

template<typename T>
double Monitor::CalcMedian(std::vector<T>& vec) const
{
    int n = vec.size();
    if (n%2 == 1)
    {
        return vec.at((n-1)/2);
    }
    else
    {
        return 0.5*(vec.at(n/2-1) + vec.at(n/2));
    }
}

template<int N, typename T>
double Monitor::CalcNthMoment(std::vector<T>& vec) const
{
    ;
}
