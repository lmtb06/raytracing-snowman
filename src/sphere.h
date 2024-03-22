#pragma once

#include "vec3.h"
#include "hittable.h"

struct Sphere : public Hittable
{
    Vec3 center;
    double radius;

    Sphere(const Vec3 &center, double radius) : center(center), radius(radius) {}

    bool hit(const Ray &ray, HitRecord &record, double tMin, double tMax) const override
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
        double nearestT = t1;
        if (nearestT < tMin || nearestT > tMax)
        {
            nearestT = t2;
            if (nearestT < tMin || nearestT > tMax)
            {
                return false;
            }
        }

        record.t = nearestT;
        record.point = ray.at(nearestT);
        record.normal = (record.point - center) / radius;

        return true;
    }
};