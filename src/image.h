#pragma once

#include "color.h"
#include <vector>
#include <fstream>
#include "stb_image_write.h"
#include <memory>

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

    std::unique_ptr<unsigned char[]> getDataSTBFormat() const
    {
        // Create a dynamic array to hold the image data
        const int channels = 3;
        auto data = std::make_unique<unsigned char[]>(width * height * channels);

        // Copy pixel data to the array
        for (int j = 0; j < height; ++j)
        {
            for (int i = 0; i < width; ++i)
            {
                Color color = getPixel(i, j);
                int index = (j * width + i) * channels;
                data[index + 0] = static_cast<unsigned char>(color.r * 255);
                data[index + 1] = static_cast<unsigned char>(color.g * 255);
                data[index + 2] = static_cast<unsigned char>(color.b * 255);
            }
        }

        return data;
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

    void savePNG(const std::string &filename) const
    {
        // Save the image data to a PNG file
        auto data = getDataSTBFormat();
        stbi_write_png(filename.c_str(), width, height, 3, data.get(), width * 3);
    }
};