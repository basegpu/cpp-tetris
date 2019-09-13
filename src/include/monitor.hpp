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
        Min,
        Max,
        Median,
        Mean,
        Variance,
        Skewness
    };

    typedef std::map<Statistics, double> Stats;
    Stats GetScoreStatistics();
    Stats GetTimeStatistics();

private:
    std::vector<int> Scores;
    std::vector<double> Times;

    template<typename T>
    Stats CalcStatistics(std::vector<T>& vec);
    template<typename T>
    double CalcMedian(std::vector<T>& vec) const;
    template<int N, typename T>
    double CalcNthMoment(std::vector<T>& vec) const;
};

#endif