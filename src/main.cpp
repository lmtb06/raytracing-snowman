#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vec3.h"
#include "image.h"
#include "camera.h"
#include "sphere.h"
#include "hittable.h"

void drawSimpleImage(int width = 800, int height = 600)
{
    double fov = 50;
    Point3 position(0, 20, -100);
    Vec3 direction(0, 0, 1);
    Vec3 up(0, 1, 0);

    Camera camera(width / ((float)height), fov, position, direction, up, 10);

    HittableList world;
    // Sphere terre(Vec3(0, -100.5, 2), 100, std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0)));
    Sphere basBonhomme(Vec3(0, 0, 5), 10, std::make_shared<Lambertian>(Color(0.8, 0.3, 0.3)));
    Sphere hautBonhomme(Vec3(0, 13, 5), 8, std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.1));
    Sphere teteBonhomme(Vec3(0, 24, 5), 5, std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.1));
    // world.add(std::make_shared<Sphere>(terre));
    world.add(std::make_shared<Sphere>(basBonhomme));
    world.add(std::make_shared<Sphere>(hautBonhomme));
    world.add(std::make_shared<Sphere>(teteBonhomme));

    Image image = camera.render(world, width, height);

    image.savePNG("image.png");
}

int main()
{
    int width = 1000;
    int height = (int)width / (4./3.);
    drawSimpleImage(width, height);
    return 0;
}