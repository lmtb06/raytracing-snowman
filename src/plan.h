#pragma once

#include "vec3.h"
#include "hittable.h"
#include "ray.h"
#include "material.h"
#include <memory>

struct Plan : public Hittable
{
    Vec3 normal;
    Point3 pointPlan;
    std::shared_ptr<Material> material;
    AABB bBox;

    Plan(const Vec3 &normal, Point3 pointPlan, std::shared_ptr<Material> material) : normal(normal), pointPlan(pointPlan), material(material)
    {
        Point3 min = Point3(-INFINITY, -INFINITY, -INFINITY);
        Point3 max = Point3(INFINITY, INFINITY, INFINITY);
        bBox = AABB(min, max);
    }

    bool hit(const Ray &ray, HitRecord &record, const Interval &interval = Interval(0.001, INFINITY)) const override
    {
        double denominator = normal.dot(ray.direction);

        if (almostEqualsZero(denominator))
        {
            return false;
        }

        Vec3 originToPlan = pointPlan - ray.origin;
        double t = originToPlan.dot(normal) / denominator;

        if (!interval.contains(t))
        {
            return false;
        }

        record.tInterval = Interval(t, t);
        record.point = ray.at(record.tInterval.min);
        record.normal = normal;
        record.material = material;
        return true;
    }

    AABB boundingBox() const override
    {
        return bBox;
    }
};