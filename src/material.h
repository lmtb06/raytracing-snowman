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