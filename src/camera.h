#pragma once

#include "vec3.h"
#include "ray.h"
#include "utils.h"
#include "hittable.h"
#include <iostream>
#include <random>

struct Camera
{
    Point3 position;
    Point3 upperLeftCorner;
    Vec3 leftToRight;
    Vec3 downToUp;
    int maxDepth;
    int samplesPerPixel;
    double viewportWidth;
    double viewportHeight;

    Camera(double aspectRatio, double fovHoriz, const Point3 &position, const Vec3 &cameraForwardDirection, const Vec3 &cameraUpDirection, int maxDepth = 3, int samplesPerPixel = 10) : maxDepth(maxDepth), samplesPerPixel(samplesPerPixel), position(position)
    {
        double theta = deg2rad(fovHoriz);
        viewportWidth = 2 * tan(theta / 2);
        viewportHeight = viewportWidth / aspectRatio;

        Vec3 z = cameraForwardDirection.normalize();
        Vec3 x = cameraUpDirection.cross(z).normalize();
        Vec3 y = z.cross(x).normalize();

        leftToRight = viewportWidth * x;
        downToUp = viewportHeight * y;
        Vec3 centerToLeft = -(viewportWidth / 2.0) * x;
        Vec3 centerToTop = (viewportHeight / 2.0) * y;
        upperLeftCorner = position + centerToLeft + centerToTop + z;
    }

    void setPosition(const Point3 &position)
    {
        Vec3 direction = position - this->position;
        this->position = position;
        upperLeftCorner = upperLeftCorner + direction;
    }

    Ray getRay(int u, int v, int width, int height) const
    {
        Vec3 delta_u = leftToRight / width;
        Vec3 delta_v = -downToUp / height;
        Point3 centrePixel = upperLeftCorner + u * delta_u + v * delta_v;
        double px = -0.5 + randomDouble();
        double py = -0.5 + randomDouble();
        Point3 samplePixel(px * delta_u + py * delta_v);
        samplePixel = centrePixel + samplePixel;
        Vec3 direction = samplePixel - position;

        return Ray(position, direction);
    }

    Color rayColor(const Ray &ray, const Hittable &world, double tMin = 0.001, double tMax = INFINITY, int depth = 3) const
    {
        HitRecord record;
        if (depth <= 0)
            return Color(0, 0, 0);

        if (world.hit(ray, record, tMin, tMax))
        {
            Vec3 direction = record.normal + randomUnitVector();
            return 0.1 * rayColor(Ray(record.point, direction), world, tMin, tMax, depth - 1);
            // return (Color)(0.5 * ((record.normal + Vec3(1, 1, 1))));
        }

        Vec3 unitDirection = ray.direction.normalize();
        double t = 0.5 * (unitDirection.y + 1.0);
        return (Color)((1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0));
    }

        Image render(const Hittable &world, int width, int height) const
    {
        double scale = 1.0 / samplesPerPixel;
        Image image(width, height);
        for (int j = 0; j < image.height; ++j)
        {
            for (int i = 0; i < image.width; ++i)
            {
                Vec3 pixelColor(0, 0, 0);
                for (int s = 0; s < samplesPerPixel; ++s)
                {
                    Ray ray = getRay(i, j, width, height);
                    pixelColor = pixelColor + rayColor(ray, world, 0.001, INFINITY, maxDepth);
                }
                pixelColor = pixelColor * scale;

                image.setPixel(i, j, ((Color)pixelColor).linearToGamma());
            }
        }
        return image;
    }
};