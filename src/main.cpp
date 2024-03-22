#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vec3.h"
#include "color.h"
#include "image.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"
#include "hittable.h"

bool hitSphere(const Sphere &sphere, const Ray &ray, HitRecord &record)
{
    Vec3 centerOrigin = ray.origin - sphere.center;
    double a = ray.direction.dot(ray.direction);
    double half_b = centerOrigin.dot(ray.direction);
    double c = centerOrigin.dot(centerOrigin) - sphere.radius * sphere.radius;
    double discriminant = half_b * half_b - a * c;

    if (discriminant < 0)
    {
        return false;
    }

    double t1 = (-half_b - sqrt(discriminant)) / a;
    double t2 = (-half_b + sqrt(discriminant)) / a;
    double minT = t1;
    if (abs(t2) < abs(t1))
    {
        minT = t2;
    }
    record.t = minT;
    record.point = ray.at(minT);
    record.normal = (record.point - sphere.center) / sphere.radius;

    return true;
}

Color rayColor(const Ray &ray, const Hittable &world)

{
    HitRecord record;
    if (world.hit(ray, record))
    {
        return (Color)(0.5 * (Vec3(1, 1, 1) + record.normal));
    }

    Vec3 unitDirection = ray.direction.normalize();
    double t = 0.5 * (unitDirection.y + 1.0);
    return (Color)((1.0 - t) * Vec3(1.0, 1.0, 1.0) + t * Vec3(0.5, 0.7, 1.0));
}

void drawSimpleImage(int width = 800, int height = 600)
{
    // Créer une image de width par height pixels
    Image image(width, height);
    double aspectRatio = double(width) / height;
    double fov = 80;
    Point3 position(0, 0, 0);
    Vec3 direction(0, 0, 1);
    Vec3 up(0, 1, 0);

    Camera camera(aspectRatio, fov, position, direction, up);
    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3(0, 0, 1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, -1), 100));

    // Parcourir tous les pixels de l'image
    for (int j = 0; j < image.height; ++j)
    {
        for (int i = 0; i < image.width; ++i)
        {
            double u = double(i) / (image.width - 1);
            double v = double(j) / (image.height - 1);

            // Calculer une couleur en fonction de (u, v)
            Ray ray = camera.getRay(u, v);

            // Définir la couleur du pixel
            image.setPixel(i, j, rayColor(ray, world));
        }
    }

    // Enregistrer l'image dans un fichier PPM
    image.savePNG("image.png");
}

int main()
{
    drawSimpleImage(400, 400);
    return 0;
}