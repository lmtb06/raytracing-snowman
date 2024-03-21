#pragma once

#include "color.h"
#include <vector>
#include <fstream>

struct Image
{
    int width, height;
    std::vector<Color> pixels;

    Image(int width, int height) : width(width), height(height), pixels(width * height) {}

    void setPixel(int i, int j, const Color &color)
    {
        pixels[i + j * width] = color;
    }

    Color getPixel(int i, int j) const
    {
        return pixels[i + j * width];
    }

    void savePPM(const std::string &filename) const
    {
        std::ofstream file(filename, std::ios::binary);
        file << "P3\n"
             << width << ' ' << height << '\n'
             << "255\n";
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                Color color = getPixel(i, j);
                file << static_cast<int>(color.r * 255) << ' '
                     << static_cast<int>(color.g * 255) << ' '
                     << static_cast<int>(color.b * 255) << '\n';
            }
        }
    }
};