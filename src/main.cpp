#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "vec3.h"
#include "color.h"
#include "image.h"
#include "ray.h"
#include "camera.h"
#include "sphere.h"

bool hitSphere(const Sphere& sphere, const Ray& ray){
    double a = ray.direction.dot(ray.direction);
    double b = 2*ray.direction.dot(ray.origin - sphere.center);
    double c = (ray.origin - sphere.center).dot(ray.origin - sphere.center) - sphere.radius*sphere.radius;
    double discriminant = b*b - 4*a*c;
    return discriminant >= 0;
}

Color rayColor(const Ray &ray)
{
    if (hitSphere(Sphere(Point3(0, 0, -4), 0.6), ray))
    {
        return Color(1, 0, 1.);
    }

    Vec3 unitDirection = ray.direction.normalize();
    double t = 0.5 * (unitDirection.y + 1.0);
    return (1.0 - t) * Color(1.0, 1.0, 1.0) + t * Color(0.1, 0.2, 1.0);
}

void drawSimpleImage(int width = 800, int height = 600)
{
    // Créer une image de width par height pixels
    Image image(width, height);
    double aspectRatio = double(width) / height;
    double fov = 90;
    Point3 position(0, 0, 0);
    Vec3 direction(0, -0.1, -1);
    Vec3 up(0, 1, 0);

    Camera camera(aspectRatio, fov, position, direction, up);

    // Parcourir tous les pixels de l'image
    for (int j = 0; j < image.height; ++j)
    {
        for (int i = 0; i < image.width; ++i)
        {
            double u = double(i) / (image.width - 1);
            double v = ((image.height - 1) - double(j)) / (image.height - 1);

            // Calculer une couleur en fonction de (u, v)
            Ray ray = camera.getRay(u, v);

            // Définir la couleur du pixel
            image.setPixel(i, j, rayColor(ray));
        }
    }

    // Enregistrer l'image dans un fichier PPM
    image.savePNG("image.png");
}

int main()
{
    drawSimpleImage(1280, 720);
    return 0;
}