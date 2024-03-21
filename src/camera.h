#pragma once

#include "vec3.h"
#include "ray.h"
#include "utils.h"

struct Camera
{
    Point3 origin;
    Point3 lowerLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;

    Camera(double aspectRatio, double fovHoriz, const Point3& position, const Vec3& direction, const Vec3& up)
    {
        double theta = deg2rad(fovHoriz);
        double width = tan(theta / 2);
        double viewportWidth = 2.0 * width;
        double viewportHeight = viewportWidth / aspectRatio;


        origin = position;
        Vec3 w = (position - direction).normalize();
        Vec3 u = up.cross(w).normalize();
        Vec3 v = w.cross(u);

        origin = position;
        horizontal = viewportWidth * u;
        vertical = viewportHeight * v;
        lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;

    }

    Ray getRay(double u, double v) const
    {
        return Ray(origin, lowerLeftCorner + u * horizontal + v * vertical - origin);
    }

};