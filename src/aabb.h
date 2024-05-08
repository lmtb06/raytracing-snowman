#pragma once
#include "interval.h"
#include "vec3.h"
#include "ray.h"

struct AABB
{
    Interval x, y, z;

    AABB() : x(), y(), z() {}

    AABB(const Interval &x, const Interval &y, const Interval &z) : x(x), y(y), z(z) {}

    AABB(const Point3 &a, const Point3 &b)
    {
        x = Interval(a.x, b.x);
        y = Interval(a.y, b.y);
        z = Interval(a.z, b.z);
    }

    AABB(const AABB &a, const AABB &b) : x(a.x, b.x), y(a.y, b.y), z(a.z, b.z) {}

    const Interval &operator[](int i) const
    {
        return i == 0 ? x : (i == 1 ? y : z);
    }

    bool hit(const Ray &ray, Interval &t) const
    {
        for (int i = 0; i < 3; i++)
        {
            const Interval &ax = (*this)[i];
            double t0 = (ax.min - ray.origin[i]) / ray.direction[i];
            double t1 = (ax.max - ray.origin[i]) / ray.direction[i];

            Interval tInterval(t0, t1);
            if (tInterval.min > t.min)
                t.min = tInterval.min;
            if (tInterval.max < t.max)
                t.max = tInterval.max;

            if (t.max <= t.min)
                return false;
        }

        return true;
    }

    int longestAxis() const
    {
        if (x.length() > y.length())
        {
            return x.length() > z.length() ? 0 : 2;
        }
        else
        {
            return y.length() > z.length() ? 1 : 2;
        }
    }

    friend std::ostream &operator<<(std::ostream &out, const AABB &a)
    {
        return out << "x: " << a.x << ", y: " << a.y << ", z: " << a.z;
    }
};