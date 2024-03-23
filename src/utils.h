#pragma once
#include <cmath>
#include <random>

double deg2rad(double degrees)
{
    return degrees * M_PI / 180;
}

inline double randomDouble()
{
    static std::uniform_real_distribution<double> distribution(0.0, 1.0);
    static std::mt19937 generator;
    return distribution(generator);
}
