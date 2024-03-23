#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vec3.h"
#include "image.h"
#include "camera.h"
#include "sphere.h"
#include "hittable.h"

void drawSimpleImage(int width = 800, int height = 600)
{
    double fov = 90;
    Point3 position(0, 0, -1);
    Vec3 direction(0, 0, 1);
    Vec3 up(0, 1, 0);

    Camera camera(16.0 / 9.0, fov, position, direction, up);

    HittableList world;
    world.add(std::make_shared<Sphere>(Vec3(0, 0, 1), 0.5));
    world.add(std::make_shared<Sphere>(Vec3(0, -100.5, 1), 100));

    Image image = camera.render(world, width, height);

    image.savePNG("image.png");
}

int main()
{
    int width = 400;
    int height = (int)400 / (16.0 / 9.0);
    drawSimpleImage(width, height);
    return 0;
}