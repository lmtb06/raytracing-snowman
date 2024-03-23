#pragma once

#include "ray.h"
#include "color.h"
#include "hittable.h"

struct Material
{
    virtual bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation, Ray &scattered) const = 0;
};

struct Lambertian : public Material
{
    Color albedo;

    Lambertian(const Color &albedo) : albedo(albedo) {}

    bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation, Ray &scattered) const override
    {
        Vec3 scatterDirection = record.normal + randomUnitVector();
        if (scatterDirection.nearZero())
        {
            scatterDirection = record.normal;
        }

        scattered = Ray(record.point, scatterDirection);
        attenuation = albedo;
        return true;
    }
};

struct Metal : public Material
{
    Color albedo;
    double fuzz;

    Metal(const Color &albedo, double fuzz) : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}

    bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation, Ray &scattered) const override
    {
        Vec3 reflected = ray_in.direction.normalize().reflect(record.normal);
        scattered = Ray(record.point, reflected + fuzz * randomInUnitSphere());
        attenuation = albedo;
        return scattered.direction.dot(record.normal) > 0;
    }
};