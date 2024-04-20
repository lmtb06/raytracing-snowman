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

    Plan(const Vec3 &normal, Point3 pointPlan, std::shared_ptr<Material> material) : normal(normal), pointPlan(pointPlan), material(material) {}

    bool hit(const Ray &ray, HitRecord &record, double tMin, double tMax) const override
    {
        double denominator = normal.dot(ray.direction);

        if (denominator > 0)
        {
            return false;
        }

        Vec3 originToPlan = pointPlan - ray.origin;
        record.t = normal.dot(originToPlan) / denominator;
        record.point = ray.at(record.t);
        record.normal = normal;
        record.material = material;

        return true;
    }
};