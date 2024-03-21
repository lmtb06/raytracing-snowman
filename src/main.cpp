#include "vec3.h"
#include "color.h"
#include "image.h"

int main()
{
    // Créer une image de 800 par 600 pixels
    Image image(800, 600);

    // Parcourir tous les pixels de l'image
    for (int j = 0; j < image.height; ++j) {
        for (int i = 0; i < image.width; ++i) {
            double u = double(i) / (image.width - 1);
            double v = double(j) / (image.height - 1);

            // Calculer une couleur en fonction de (u, v)
            Color color(u, v, 1.0);

            // Définir la couleur du pixel
            image.setPixel(i, j, color);
        }
    }

    // Enregistrer l'image dans un fichier PPM
    image.savePPM("image.ppm");

    return 0;
}