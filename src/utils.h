#pragma once
#include <cmath>
#include <random>
#include <limits>
static std::random_device rd;
const double EPSILON = std::numeric_limits<double>::epsilon();

double deg2rad(double degrees)
{
    return degrees * M_PI / 180;
}

bool almostEqualsZero(double x, double epsilon = EPSILON)
{
    return std::abs(x) <= epsilon || std::abs(x) <= epsilon * std::abs(x);
}

inline double randomUniformDouble(double min = 0.0, double max = 1.0)
{
    static std::uniform_real_distribution<double> distribution(min, max);
    static std::mt19937 generator{rd()};
    return distribution(generator);
}

inline double randomNormalDouble(double mean = 0.0, double stdDev = 0.5)
{
    static std::normal_distribution<double> distribution(mean, stdDev);
    static std::mt19937 generator{rd()};
    return distribution(generator);
}

inline int randomUniformInt(int min = 0, int max = 1)
{
    return int(randomUniformDouble(min, max+1));
}
