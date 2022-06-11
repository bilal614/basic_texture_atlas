#include "ImageDecoder.h"
#include "ImageEncoder.h"
#include "ImageSrcDir.h"
#include <iostream>

int main(int argc, char *argv[]) 
{
    std::string directoryPath = argc > 1 ? argv[1] : "test_images";

    BasicTextureAtlas::ImageSrcDir imgSrcDir{directoryPath};

    BasicTextureAtlas::ImageDecoder decoder;

    std::vector<std::vector<unsigned char>> images;

    for(const auto& path : imgSrcDir.pngFilePathsInDir())
    {
        images.push_back(std::vector<unsigned char>{});
        auto result = decoder.decode(path, images.back(), 124, 126);
        std::cout << "result: " << result << std::endl;

    }

    std::vector<unsigned char> combinedImage;
    for(const auto& img : images)
    {
        combinedImage.insert(combinedImage.end(), img.begin(), img.end());
    }
    std::cout << "combinedImage size: " << combinedImage.size() << std::endl;
    BasicTextureAtlas::ImageEncoder encoder;

    auto outputFilePath = "test_images/test_image.png";
    auto result = encoder.encode(outputFilePath, combinedImage, 124, 744);

    std::cout << "result: " << result << std::endl;

    return result;

}