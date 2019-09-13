#ifndef MONITOR_H
#define MONITOR_H

#include "globals.hpp"
#include <vector>
#include <map>
#include <numeric>

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
    std::vector<double> Scores;
    std::vector<double> Times;

    Stats CalcStatistics(std::vector<double>& vec);

    template<class T>
    double CalcMedian(std::vector<T>& vec) const
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
    };
    
    template<class T, int N>
    static T CalcNthPower(T x)
    {
        T ret = x;
        for (int ii = 1; ii < N; ii++) {
            ret *= x;
        }
        return ret;
    };

    template<class T, int N>
    struct SumDiffNthPower {
        SumDiffNthPower(T x) : mean_(x) { };
        T operator( )(T sum, T current) {
            return sum + Monitor::CalcNthPower<T, N>(current - mean_);
        }
        T mean_;
    };

    template<class T, int N, class iter_T>
    T CalcNthMoment(iter_T first, iter_T last, T mean) const {
        size_t cnt = std::distance(first, last);
        return std::accumulate(first, last, T( ), SumDiffNthPower<T, N>(mean)) / (cnt + 1 - N);
    };
};

#endif