#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vec3.h"
#include "image.h"
#include "camera.h"
#include "sphere.h"
#include "hittable.h"
#include "plan.h"

void drawSimpleImage(int width = 800, int height = 600)
{
    HittableList world;
    Sphere boule(Vec3(2, 6, 5), 5, std::make_shared<Lambertian>(Color(0.8, 0.8, 0.0)));
    Sphere basBonhomme(Vec3(0, 0.5, 0), 0.5, std::make_shared<Dielectric>(1.5));
    Sphere hautBonhomme(basBonhomme.center + Vec3(0, 0.5+0.25, 0)
    , 0.25, std::make_shared<Dielectric>(1.5));
    Sphere hautBonhomme2(basBonhomme.center + Vec3(0, 0.5+0.25, 0)
    , -0.125, std::make_shared<Dielectric>(1.5));
    Sphere teteBonhomme(hautBonhomme.center + Vec3(0, 0.25+0.125, 0)
    , 0.125, std::make_shared<Metal>(Color(0.8, 0.6, 0.2), 0.1));
    Plan plan(Vec3(0, 1, 0), Point3(0, 0, 0), std::make_shared<Lambertian>(Color(0.9, 0.5, 0.5)));
    world.add(std::make_shared<Sphere>(boule));
    world.add(std::make_shared<Sphere>(basBonhomme));
    world.add(std::make_shared<Sphere>(hautBonhomme));
    world.add(std::make_shared<Sphere>(hautBonhomme2));
    world.add(std::make_shared<Sphere>(teteBonhomme));
    world.add(std::make_shared<Plan>(plan));

    double fov = 40;
    Point3 position(teteBonhomme.center + Vec3(0, 0.5,-5));
    Vec3 lookAt(teteBonhomme.center);
    Vec3 up(0, 1, 0);

    Camera camera(width / ((float)height), fov, position, lookAt, up, 50, 50);

    Image image = camera.render(world, width);

    image.savePNG("image.png");
}



int main()
{
    int width = 800;
    int height = (int)width / (4. / 3.);
    drawSimpleImage(width, height);
    return 0;
}