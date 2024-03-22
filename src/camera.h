#pragma once

#include "vec3.h"
#include "ray.h"
#include "utils.h"
#include <iostream>

struct Camera
{
    Point3 origin;
    Point3 upperLeftCorner;
    Vec3 horizontal;
    Vec3 vertical;

    Camera(double aspectRatio, double fovHoriz, const Point3& position, const Vec3& cameraForwardDirection, const Vec3& cameraUpDirection)
    {
        double theta = deg2rad(fovHoriz);
        double width = tan(theta / 2);
        double viewportWidth = 2.0 * width;
        double viewportHeight = viewportWidth / aspectRatio;


        origin = position;
        Vec3 w = cameraForwardDirection.normalize();
        Vec3 u = cameraUpDirection.cross(w).normalize();
        Vec3 v = w.cross(u).normalize();

        origin = position;
        horizontal = viewportWidth * u;
        vertical = viewportHeight * v;
        upperLeftCorner = origin - horizontal / 2 + vertical / 2 + w;

    }

    Ray getRay(double u, double v) const
    {
        return Ray(origin, upperLeftCorner + u * horizontal - v * vertical - origin);
    }

};