#pragma once

#include <cmath>

struct Vec3
{
    double x, y, z;

    Vec3(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}

    Vec3 operator+(const Vec3 &v) const
    {
        return Vec3(x + v.x, y + v.y, z + v.z);
    }

    Vec3 operator-(const Vec3 &v) const
    {
        return Vec3(x - v.x, y - v.y, z - v.z);
    }

    Vec3 operator*(double s) const
    {
        return Vec3(x * s, y * s, z * s);
    }

    Vec3 operator*(const Vec3 &v) const
    {
        return Vec3(x * v.x, y * v.y, z * v.z);
    }

    Vec3 operator/(double s) const
    {
        return Vec3(x / s, y / s, z / s);
    }

    Vec3 operator-() const
    {
        return Vec3(-x, -y, -z);
    }

    double dot(const Vec3 &v) const
    {
        return x * v.x + y * v.y + z * v.z;
    }

    Vec3 cross(const Vec3 &v) const
    {
        return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
    }

    double norm() const
    {
        return std::sqrt(x * x + y * y + z * z);
    }
    Vec3 normalize() const
    {
        return *this / norm();
    }
};

inline Vec3 operator*(double t, const Vec3 &v)
{
    return v * t;
}

using Point3 = Vec3;