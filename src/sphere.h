#pragma once

#include "vec3.h"
#include "hittable.h"
#include "ray.h"
#include "material.h"
#include <memory>

struct Sphere : public Hittable
{
    Vec3 center;
    double radius;
    std::shared_ptr<Material> material;

    Sphere(const Vec3 &center, double radius, std::shared_ptr<Material> material) : center(center), radius(radius), material(material) {}

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
        double smallestT = t1;

        if (t2 < t1 && tMin <= t2 && t2 <= tMax)
        {
            smallestT = t2;
        }

        if (smallestT < tMin || smallestT > tMax)
        {
            return false;
        }

        record.t = smallestT;
        record.point = ray.at(smallestT);
        record.normal = (record.point - center) / radius;
        record.material = material;

        return true;
    }
};