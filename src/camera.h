#pragma once

#include "vec3.h"
#include "ray.h"
#include "utils.h"
#include "hittable.h"
#include "image.h"
#include "color.h"
#include "material.h"
#include "interval.h"
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
    Color backgroundColor;

    Camera(double aspectRatio, double fovVertical, const Point3 &position, const Point3 &lookAt, const Vec3 &upDirection, int maxDepth = 3, int samplesPerPixel = 10, const Color backgroundColor = Color(0, 0, 0)) : maxDepth(maxDepth), samplesPerPixel(samplesPerPixel), position(position), backgroundColor(backgroundColor)
    {
        double theta = deg2rad(fovVertical);
        viewportHeight = 2 * tan(theta / 2);
        viewportWidth = viewportHeight * aspectRatio;

        setPosition(position, lookAt, upDirection);
    }

    void setPosition(const Point3 &position, const Point3 &lookAt, const Vec3 &upDirection)
    {
        Vec3 z = (lookAt - position).normalize();
        Vec3 x = upDirection.cross(z).normalize();
        Vec3 y = z.cross(x).normalize();

        leftToRight = viewportWidth * x;
        downToUp = viewportHeight * y;
        Vec3 centerToLeft = -(viewportWidth / 2.0) * x;
        Vec3 centerToTop = (viewportHeight / 2.0) * y;
        upperLeftCorner = position + centerToLeft + centerToTop + z;
    }

    Ray getRay(int u, int v, int width, int height) const
    {
        Vec3 delta_u = leftToRight / width;
        Vec3 delta_v = -downToUp / height;
        Point3 centrePixel = upperLeftCorner + u * delta_u + v * delta_v;
        double px = randomUniformDouble(-0.5, 0.5);
        double py = randomUniformDouble(-0.5, 0.5);
        Point3 samplePixel(px * delta_u + py * delta_v);
        samplePixel = centrePixel + samplePixel;
        Vec3 direction = samplePixel - position;

        return Ray(position, direction);
    }

    Color rayColor(const Ray &ray, const Hittable &world, const Interval &interval = Interval(0.001, INFINITY), int depth = 3) const
    {
        HitRecord record;
        if (depth <= 0)
            return Color(0, 0, 0);

        if (world.hit(ray, record, interval))
        {
            Ray scattered;
            Color attenuation(0, 0, 0);
            Color colorFromScatter(0, 0, 0);
            Color colorFromEmission = record.material->emitted(record.point);

            if (ray.direction.dot(record.normal) > 0)
            {
                record.normal = -record.normal;
            }

            record.normal = record.normal.normalize();

            if (record.material->scatter(ray, record, attenuation, scattered))
            {
                double lightStrength = fabs(record.normal.dot(scattered.direction.normalize()));
                colorFromScatter = attenuation * rayColor(scattered, world, interval, depth - 1);
                // colorFromScatter = colorFromScatter * lightStrength;
            }

            return colorFromScatter + colorFromEmission;
        }

        // return backgroundColor;
        double t = 0.5 * (ray.direction.normalize().y + 1.0);
        return (Color)((1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0));
    }

    Image render(const Hittable &world, int width) const
    {
        int height = int(viewportHeight * width / viewportWidth);
        int progress = 0;
        int lastPercentage = -1;
        int totalPixels = width * height;
        double scale = 1.0 / samplesPerPixel;
        Image image(width, height);

#pragma omp parallel for collapse(2)
        for (int j = 0; j < image.height; ++j)
        {
            for (int i = 0; i < image.width; ++i)
            {
                Color pixelColor(0, 0, 0);
                for (int s = 0; s < samplesPerPixel; ++s)
                {
                    Ray ray = getRay(i, j, width, height);
                    pixelColor = pixelColor + rayColor(ray, world, Interval(0.001, INFINITY), maxDepth);
                }
                pixelColor = pixelColor * scale;
                pixelColor = pixelColor.linearToGamma();
                pixelColor.clamp();
                image.setPixel(i, j, pixelColor);

// Print progress
#pragma omp critical
                {
                    int currentPercentage = (++progress * 100) / totalPixels;
                    if (currentPercentage != lastPercentage)
                    {
                        lastPercentage = currentPercentage;
                        std::cout << "\rProgress: " << currentPercentage << "%" << std::flush;
                    }
                }
            }
        }
        std::cout << std::endl;
        return image;
    }
};