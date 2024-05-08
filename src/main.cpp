#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vec3.h"
#include "image.h"
#include "camera.h"
#include "sphere.h"
#include "hittable.h"
#include "plan.h"
#include "bvh.h"
#include <chrono>

void drawSimpleImage(int width = 800, int height = 600)
{
    HittableList world;
    auto groundMaterial = std::make_shared<Metal>(Color(0.4, 0.4, 0.4), 0.3);
    auto material1 = std::make_shared<Lambertian>(Color(0.8, 0.8, 0.5));
    auto material2 = std::make_shared<Dielectric>(1.5);
    auto material3 = std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.001);
    auto light = std::make_shared<Light>(
        Color(0.8, 0.5, 0.5),
        1);
    auto light2 = std::make_shared<Light>(
        Color(0.0, 0.5, 0.5),
        1);

    Sphere boule(Vec3(2, 10, 5), 5, light);
    Sphere basBonhomme(Vec3(0, 0.5, 0), 0.5, material1);
    Sphere hautBonhomme(basBonhomme.center + Vec3(0, 0.5 + 0.25, 0), 0.25, material2);
    Sphere hautBonhomme2(basBonhomme.center + Vec3(0, 0.5 + 0.25, 0), 0.125, light2);
    Sphere teteBonhomme(hautBonhomme.center + Vec3(0, 0.25 + 0.125, 0), 0.125, material3);
    Plan plan(Vec3(0, 1, 0), Point3(0, 0, 0), groundMaterial);
    world.add(std::make_shared<Sphere>(boule));
    world.add(std::make_shared<Sphere>(basBonhomme));
    world.add(std::make_shared<Sphere>(hautBonhomme));
    world.add(std::make_shared<Sphere>(hautBonhomme2));
    world.add(std::make_shared<Sphere>(teteBonhomme));
    world.add(std::make_shared<Plan>(plan));

    double fov = 30;
    Point3 position(teteBonhomme.center + Vec3(0, 0.5, -5));
    // Point3 position(basBonhomme.center);
    Vec3 lookAt(hautBonhomme.center);
    Vec3 up(0, 1, 0);

    Camera camera(width / ((float)height), fov, position, lookAt, up, 20, 100, Color(0.05, 0.05, 0.05));
    auto start = std::chrono::high_resolution_clock::now();
    // Image image = camera.render(world, width);
    Image image = camera.render(BVHNode(world), width);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Time: " << duration.count() << "ms" << std::endl;

    image.savePNG("image.png");
}

int main()
{
    int width = 800;
    int height = (int)width / (4. / 3.);
    drawSimpleImage(width, height);
    return 0;
}