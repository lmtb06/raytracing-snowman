#pragma once

#include "vec3.h"
#include <algorithm>

// Couleur RGB normalisée (comprise entre 0 et 1)
struct Color
{
    double r, g, b;

    Color(double r = 0, double g = 0, double b = 0) : r(r), g(g), b(b) {
        clamp();
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
};

inline Color operator*(double s, const Color &c)
{
    return c * s;
}
