#pragma once

#include "ray.h"
#include <memory>
#include <vector>
#include "aabb.h"
struct Material;

struct HitRecord
{
    Point3 point;
    Vec3 normal;
    Interval tInterval;
    std::shared_ptr<Material> material;
};

struct Hittable
{
    virtual bool hit(const Ray &ray, HitRecord &record, const Interval &interval = Interval(0.001, INFINITY)) const = 0;
    virtual AABB boundingBox() const = 0;
};

struct HittableList : public Hittable
{
    std::vector<std::shared_ptr<Hittable>> objects;
    AABB bBox;

    HittableList()
    {
        bBox = AABB();
    }
    HittableList(std::shared_ptr<Hittable> object)
    {
        bBox = object->boundingBox();
        add(object);
    }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object)
    {
        objects.push_back(object);
        bBox = AABB(bBox, object->boundingBox());
    }

    virtual bool hit(const Ray &ray, HitRecord &record, const Interval &interval = Interval(0.001, INFINITY)) const override
    {
        HitRecord tempRecord;
        bool hitAnything = false;
        double closestSoFar = interval.max;
        double farthestSoFar = interval.min;

        for (const auto &object : objects)
        {
            if (object->hit(ray, tempRecord, Interval(interval.min, closestSoFar)))
            {

                if (tempRecord.tInterval.min < closestSoFar)
                {
                    hitAnything = true;
                    closestSoFar = tempRecord.tInterval.min;
                    record = tempRecord;
                }

                if (farthestSoFar < tempRecord.tInterval.max)
                {
                    farthestSoFar = tempRecord.tInterval.max;
                }
            }
        }
        record.tInterval = Interval(closestSoFar, farthestSoFar);
        return hitAnything;
    }

    virtual AABB boundingBox() const override
    {
        return bBox;
    }
};