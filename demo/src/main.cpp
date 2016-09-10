/**
 * Application entry point.
 *
 * @author Raoul Harel
 * @url github.com/rharel/cpp-diamond-square
 */

#include <iostream>
#include <limits>
#include <vector>

#include <freeimage/FreeImagePlus.h>

#include <diamond_square/diamond_square.hpp>


using namespace diamond_square;

typedef HeightMap<float> Map;
typedef HeightMapGenerator<float> MapGenerator;
typedef HeightMapLayer<float> MapLayer;

void ConvertToGrayscale
(
    const Map& map,
    std::vector<BYTE>& bytes
)
{
    float min_value =  std::numeric_limits<float>::infinity();
    float max_value = -std::numeric_limits<float>::infinity();
    for (unsigned int i = 0; i < map.size(); ++i)
    {
        const float value = map.data()[i];
        min_value = min(min_value, value);
        max_value = max(max_value, value);
    }
    const float range = max_value - min_value;

    bytes.resize(map.size());
    for (unsigned int i = 0; i < map.size(); ++i)
    {
        const float value = map.data()[i];
        bytes.at(i) = static_cast<BYTE>
        (
            255 * 
            (value - min_value) / 
            range
        );
    }
}
BOOL SaveImage
(
    const unsigned int width,
    const unsigned int height,
    const BYTE* bytes, 
    const char* path
)
{
    fipImage image
    (
        FIT_BITMAP, 
        width, height,
        24
    );
    unsigned int i = 0;
    for (size_t x = 0; x < width; ++x)
    {
        for (size_t y = 0; y < height; ++y)
        {
            BYTE intensity = bytes[i];

            RGBQUAD color;
            color.rgbRed = intensity;
            color.rgbGreen = intensity;
            color.rgbBlue = intensity;
            
            image.setPixelColor(x, y, &color);
            
            ++i;
        }
    }
    return image.save(path);
}
bool SaveAsImage
(
    const Map& map,
    const char* path
)
{
    std::vector<BYTE> bytes;
    ConvertToGrayscale(map, bytes);
    return SaveImage
    (
        map.width(), map.height(),
        bytes.data(),
        path
    ) != 0;
}

int main()
{
    static const int SUCCESS = 0;
    static const int FAILURE = 1;

    static const char* MAP_IMAGE_PATH = "./map.bmp";
    
    NoiseGenerator<float> noise_generator
    (
        [](float t)  // Exponential easing function
        {
            return (t == 1.0f) ? 1.0f : -std::pow(2.0f, -10.0f * t) + 1.0f;
        },
        0.0f, 50.0f
    );
    MapGenerator generator(9, noise_generator);
    
    generator.map().At(256, 256) = 300;
    generator.Generate();

    std::cout << "Saving image to: " 
              << MAP_IMAGE_PATH
              << std::endl;
    const bool image_save_succesful = SaveAsImage
    (
        generator.map(),
        MAP_IMAGE_PATH
    );
    if (image_save_succesful)
    {
        std::cout << "Success!" << std::endl; 
    }

    return image_save_succesful ?
           SUCCESS : FAILURE;
}
