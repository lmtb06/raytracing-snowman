#pragma once

#include <cmath>
#include <iostream>

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

    static Vec3 random()
    {
        return Vec3(drand48(), drand48(), drand48());
    }

    static Vec3 random(double min, double max)
    {
        return Vec3(drand48() * (max - min) + min, drand48() * (max - min) + min, drand48() * (max - min) + min);
    }

    bool nearZero() const
    {
        const double s = 1e-8;
        return (fabs(x) < s) && (fabs(y) < s) && (fabs(z) < s);
    }
};

inline Vec3 operator*(double t, const Vec3 &v)
{
    return v * t;
}

inline Vec3 randomInUnitSphere()
{
    while (true)
    {
        Vec3 p = Vec3::random(-1, 1);
        if (p.dot(p) < 1)
            return p;
    }
}

inline Vec3 randomUnitVector()
{
    return randomInUnitSphere().normalize();
}

inline Vec3 randomOnHemisphere(const Vec3 &normal)
{
    Vec3 onUnitSphere = randomUnitVector();
    if (onUnitSphere.dot(normal) > 0.0)
    {
        return onUnitSphere;
    }
    else
    {
        return -onUnitSphere;
    }
}

inline std::ostream &operator<<(std::ostream &os, const Vec3 &v)
{
    os << "(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}

using Point3 = Vec3;