#pragma once

#include "vec3.h"
#include "utils.h"
#include <algorithm>

struct Color
{
    double r, g, b;

    Color(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b)
    {
    }

    explicit Color(const Vec3 &v) : r(v.x), g(v.y), b(v.z) {}

    operator Vec3() const
    {
        return Vec3(r, g, b);
    }

    Color operator+(const Color &c) const
    {
        return Color(r + c.r, g + c.g, b + c.b);
    }

    Color operator-(const Color &c) const
    {
        return Color(r - c.r, g - c.g, b - c.b);
    }

    Color operator*(double s) const
    {
        return Color(r * s, g * s, b * s);
    }

    Color operator*(const Color &c) const
    {
        return Color(r * c.r, g * c.g, b * c.b);
    }

    Color operator/(double s) const
    {
        return Color(r / s, g / s, b / s);
    }

    void clamp()
    {
        r = std::clamp(r, 0.0, 1.0);
        g = std::clamp(g, 0.0, 1.0);
        b = std::clamp(b, 0.0, 1.0);
    }

    Color linearToGamma() const
    {
        double rComp = 0.0;
        double gComp = 0.0;
        double bComp = 0.0;
        if (r > 0)
        {
            rComp = std::sqrt(r);
        }
        if (g > 0)
        {
            gComp = std::sqrt(g);
        }
        if (b > 0)
        {
            bComp = std::sqrt(b);
        }

        return Color(
            rComp, 
            gComp,
            bComp
            );
    }

    static Color random(double min = 0.0, double max = 1.0)
    {
        return Color(randomUniformDouble(min, max), randomUniformDouble(min, max), randomUniformDouble(min, max));
    }
};

inline Color operator*(double s, const Color &c)
{
    return c * s;
}
