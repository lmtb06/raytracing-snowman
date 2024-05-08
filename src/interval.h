#pragma once
#include <algorithm>

struct Interval
{
    double min;
    double max;

    Interval() : min(0.0), max(0.0) {}

    Interval(double a, double b) : min(std::min(a, b)), max(std::max(a, b))
    {
    }

    Interval(const Interval &a, const Interval &b) : min(std::min(a.min, b.min)), max(std::max(a.max, b.max)) {}

    void update(double a, double b)
    {
        min = std::min(a, b);
        max = std::max(a, b);
    }

    bool contains(double x) const
    {
        return (x >= min) && (x <= max);
    }

    bool contains(const Interval &other) const
    {
        return (other.min >= min) && (other.max <= max);
    }

    double length() const
    {
        return max - min;
    }

    bool overlaps(const Interval &other) const
    {
        return std::max(min, other.min) <= std::min(max, other.max);
    }

    double clamp(double x) const
    {
        return std::clamp(x, min, max);
    }

    Interval expand(double x) const
    {
        auto padding = x / 2;
        return Interval(min - padding, max + padding);
    }

    friend std::ostream &operator<<(std::ostream &out, const Interval &i)
    {
        return out << "[" << i.min << ", " << i.max << "]";
    }
};