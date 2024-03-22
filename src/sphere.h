#pragma once

#include "vec3.h"

struct Sphere
{
    Vec3 center;
    double radius;

    Sphere(const Vec3 &center, double radius) : center(center), radius(radius) {}
};