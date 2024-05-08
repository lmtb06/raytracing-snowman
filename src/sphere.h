#pragma once

#include "vec3.h"
#include "hittable.h"
#include "ray.h"
#include "material.h"
#include <memory>

struct Sphere : public Hittable
{
    Point3 center;
    double radius;
    std::shared_ptr<Material> material;
    AABB bBox;

    Sphere(const Point3 &center, double radius, std::shared_ptr<Material> material) : center(center), radius(radius), material(material)
    {
        Point3 min = center - Vec3(radius, radius, radius);
        Point3 max = center + Vec3(radius, radius, radius);
        bBox = AABB(min, max);
    }

    bool hit(const Ray &ray, HitRecord &record, const Interval &interval = Interval(0.001, INFINITY)) const override
    {
        Vec3 centerOrigin = ray.origin - center;
        double a = ray.direction.dot(ray.direction);
        double half_b = centerOrigin.dot(ray.direction);
        double c = centerOrigin.dot(centerOrigin) - radius * radius;
        double discriminant = half_b * half_b - a * c;

        if (discriminant < 0)
        {
            return false;
        }

        double t1 = (-half_b - sqrt(discriminant)) / a;
        double t2 = (-half_b + sqrt(discriminant)) / a;
        Interval tInterval(t1, t2);
        record.tInterval = tInterval;

        if (!interval.contains(tInterval.min))
        {
            record.tInterval.update(tInterval.max, tInterval.max);
        }
        if (!interval.contains(tInterval.max))
        {
            record.tInterval.update(tInterval.min, tInterval.min);
        }

        if (!interval.contains(tInterval.min) && !interval.contains(tInterval.max))
        {
            return false;
        }

        record.point = ray.at(record.tInterval.min);
        record.normal = (record.point - center) / radius;
        record.material = material;

        return true;
    }

    AABB boundingBox() const override
    {
        return bBox;
    }
};