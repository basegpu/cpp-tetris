#ifndef MONITOR_H
#define MONITOR_H

#include "globals.hpp"
#include <vector>
#include <map>

class Monitor
{
public:
    void AddOutput(const int& score, const double& time);

    enum class Statistics : int {
        Mean,
        StandardDeviation,
        Variance,
        Median,
        Min,
        Max,
        Skewness
    };

    std::map<Statistics, double> GetScoreStatistics();
    std::map<Statistics, double> GetTimeStatistics();

private:
    std::vector<int> Scores;
    std::vector<double> Times;

    template<typename T>
    std::map<Statistics, double> CalcStatistics(std::vector<T>& vec);
};

#endif