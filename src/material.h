#pragma once

#include "ray.h"
#include "color.h"
#include "hittable.h"
#include "utils.h"

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

struct Dielectric : public Material
{
    double refractionIndex;

    Dielectric(double refractionIndex) : refractionIndex(refractionIndex) {}

    bool scatter(const Ray &ray_in, const HitRecord &record, Color &attenuation, Ray &scattered) const override
    {
        attenuation = Color(1, 1, 1);
        double refractionRatio = record.normal.dot(ray_in.direction) > 0 ? refractionIndex : 1.0 / refractionIndex;
        Vec3 unitDirection = ray_in.direction.normalize();
        double cosTheta = fmin(-unitDirection.dot(record.normal), 1.0);
        double sinTheta = sqrt(1.0 - cosTheta * cosTheta);

        bool cannotRefract = refractionRatio * sinTheta > 1.0;
        Vec3 direction;

        if (cannotRefract || reflectance(cosTheta, refractionRatio) > randomDouble())
        {
            direction = unitDirection.reflect(record.normal);
        }
        else
        {
            direction = unitDirection.refract(record.normal, refractionRatio);
        }

        scattered = Ray(record.point, direction);
        return true;
    }

    double reflectance(double cosine, double refractionRatio) const
    {
        double r0 = (1 - refractionRatio) / (1 + refractionRatio);
        r0 = r0 * r0;
        return r0 + (1 - r0) * pow((1 - cosine), 5);
    }
};