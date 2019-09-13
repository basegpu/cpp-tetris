#include "globals.hpp"
#include "monitor.hpp"
#include <vector>
#include <map>
#include <exception>


void Monitor::AddOutput(const int& score, const double& time)
{
    this->Scores.push_back(score);
    this->Times.push_back(time);
}

std::map<Monitor::Statistics, double> Monitor::GetScoreStatistics()
{
    return CalcStatistics<int>(this->Scores);
}

std::map<Monitor::Statistics, double> Monitor::GetTimeStatistics()
{
    return CalcStatistics<double>(this->Times);
}

template<typename T>
std::map<Monitor::Statistics, double> Monitor::CalcStatistics(std::vector<T>& vec)
{
    if (vec.size() <= 0)
    {
        throw std::logic_error("No data available for statistics.");
    }
    return {
        {Statistics::Mean, 1.0}
    };
}
