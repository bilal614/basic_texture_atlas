#include "ImageReel.h"

#include <iostream>
#include <map>
#include <string>

#include "ImageDecoder.h"
#include "ImageEncoder.h"
#include "ImageSrcDir.h"

namespace BasicTextureAtlas
{

struct ImageReel::Impl
{
    Impl(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder);
    void composeCombinedImage();
    ImageSrcDir& imageSrcDir;
    ImageDecoder& imageDecoder;
    ImageEncoder& imageEncoder;

    std::map<std::string, std::vector<unsigned char>> decodedImages;
    std::vector<unsigned char> combinedImage;
};

void ImageReel::Impl::composeCombinedImage()
{
    for(const auto& img : decodedImages)
    {
        combinedImage.insert(combinedImage.end(), img.second.begin(), img.second.end());
    }
}

ImageReel::Impl::Impl(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder) :
    imageSrcDir{imgSrcDir},
    imageDecoder{imgDecoder},
    imageEncoder{imgEncoder}
{
}

ImageReel::ImageReel(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder) :
    ptr{std::make_unique<Impl>(imgSrcDir, imgDecoder, imgEncoder)}
{

}

ImageReel::~ImageReel() = default;

bool ImageReel::decodePngFilesFromDir()
{
    bool result = true;
    for(const auto& path : ptr->imageSrcDir.pngFilePathsInDir())
    {
        ptr->decodedImages.insert(std::make_pair(path,  std::vector<unsigned char>{}));
        unsigned int width, height;
        if(!ptr->imageDecoder.decode(path, ptr->decodedImages[path], width, height, 124, 126))
        {
            std::cout << "ERROR: Could not decode the image: " << path << std::endl;
            result = false;
        }

    }
    return result;
}

bool ImageReel::encodeCombinedImage()
{
    ptr->composeCombinedImage();
    auto outputFilePath = "test_images/test_image.png";
    std::cout << "combinedImage size: " << ptr->combinedImage.size() << std::endl;
    return ptr->imageEncoder.encode(outputFilePath, ptr->combinedImage, 124, 744);
}

}