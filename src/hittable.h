#pragma once

#include "ray.h"
#include <memory>
#include <vector>
struct Material;

struct HitRecord
{
    Point3 point;
    Vec3 normal;
    double t;
    std::shared_ptr<Material> material;
};

struct Hittable
{
    virtual bool hit(const Ray &ray, HitRecord &record, double tMin = 0.001, double tMax = INFINITY) const = 0;
};

struct HittableList : public Hittable
{
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray &ray, HitRecord &record, double tMin = 0.001, double tMax = INFINITY) const override
    {
        HitRecord tempRecord;
        bool hitAnything = false;
        double closestSoFar = tMax;

        for (const auto &object : objects)
        {
            if (object->hit(ray, tempRecord, tMin, closestSoFar))
            {
                hitAnything = true;
                closestSoFar = tempRecord.t;
                record = tempRecord;
            }
        }

        return hitAnything;
    }
};