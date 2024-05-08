#pragma once

#include "aabb.h"
#include "hittable.h"
#include <algorithm>

struct BVHNode : public Hittable
{
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    AABB bBox;

    BVHNode(HittableList list) : BVHNode(list.objects, 0, list.objects.size())
    {
        
    }

    BVHNode(std::vector<std::shared_ptr<Hittable>> &objects, size_t start, size_t end)
    {
        bBox = AABB();
        for (size_t i = start; i < end; i++)
        {
            bBox = AABB(bBox, objects[i]->boundingBox());
        }
        int axis = bBox.longestAxis();

        auto comparator = (axis == 0)   ? boxXCompare
                          : (axis == 1) ? boxYCompare
                                        : boxZCompare;

        size_t object_span = end - start;
        if (object_span == 1)
        {
            left = right = objects[start];
        }
        else if (object_span == 2)
        {
            left = objects[start];
            right = objects[start + 1];
        }
        else
        {
            std::sort(objects.begin() + start, objects.begin() + end, comparator);

            size_t mid = start + object_span / 2;
            left = std::make_shared<BVHNode>(objects, start, mid);
            right = std::make_shared<BVHNode>(objects, mid, end);
        }
    }

    bool hit(const Ray &ray, HitRecord &record, const Interval &interval) const override
    {
        Interval tempInterval(interval);
        if (!bBox.hit(ray, tempInterval))
        {
            return false;
        }

        bool hitLeft = left->hit(ray, record, tempInterval);
        bool hitRight = right->hit(ray, record, hitLeft ? Interval(tempInterval.min, record.tInterval.min) : tempInterval);

        return hitLeft || hitRight;
    }

    AABB boundingBox() const override
    {
        return bBox;
    }

    static bool box_compare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b, int axis)
    {
        return a->boundingBox()[axis].min < b->boundingBox()[axis].min;
    }

    static bool boxXCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
    {
        return box_compare(a, b, 0);
    }

    static bool boxYCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
    {
        return box_compare(a, b, 1);
    }

    static bool boxZCompare(const std::shared_ptr<Hittable> &a, const std::shared_ptr<Hittable> &b)
    {
        return box_compare(a, b, 2);
    }
};