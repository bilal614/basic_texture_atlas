#include "ImageReel.h"

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <map>

#include "CombinedRgbaImageMetaData.h"
#include "ImageDecoder.h"
#include "ImageEncoder.h"
#include "ImageSrcDir.h"
#include "RgbaImage.h"

namespace BasicTextureAtlas
{

struct ImageReel::Impl
{
    Impl(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder, const std::string& outputPath);
    void composeCombinedImage();
    ImageSrcDir& imageSrcDir;
    ImageDecoder& imageDecoder;
    ImageEncoder& imageEncoder;

    void findLargestImageFromDecodedImages(unsigned& width, unsigned& height);
    void getImageReelSize(unsigned& width, unsigned& height);
    std::vector<CombinedRgbaImageMetaData> createRgbaImageMetaDataForCombinedImage();
    std::map<std::string, RgbaImage> decodedRgbaImages;
    std::vector<unsigned char> combinedImage;
    std::filesystem::path outputPath;
};

void ImageReel::Impl::findLargestImageFromDecodedImages(unsigned& width, unsigned& height)
{
    using pair_type = decltype(decodedRgbaImages)::value_type;
    auto max = std::max_element(decodedRgbaImages.begin(),
        decodedRgbaImages.end(),
        [](pair_type& lhs, pair_type& rhs) 
        { 
            return lhs.second.getImageSize() < rhs.second.getImageSize(); 
        });
    width = max->second.getWidth();
    height = max->second.getHeight();

    if(width == 0 || height == 0)
    {
        std::cout << "WARNING: Could not retrieve largest image width and height" << std::endl;
    }
}

void ImageReel::Impl::getImageReelSize(unsigned& width, unsigned& height)
{
    unsigned largestImageWidth = 0, largestImageHeight = 0;
    findLargestImageFromDecodedImages(largestImageWidth, largestImageHeight);
    auto nrOfImages = decodedRgbaImages.size();
    
    width = largestImageWidth;
    height = largestImageHeight*nrOfImages;
}

void ImageReel::Impl::composeCombinedImage()
{
    unsigned width = 0, height = 0;
    findLargestImageFromDecodedImages(width, height);
    for(const auto& img : decodedRgbaImages)
    {
        auto resizedRawImage = img.second.addPadding(width, height);
        combinedImage.insert(combinedImage.end(),
            resizedRawImage.begin(), 
            resizedRawImage.end());
    }
}

std::vector<CombinedRgbaImageMetaData> ImageReel::Impl::createRgbaImageMetaDataForCombinedImage()
{
    std::vector<CombinedRgbaImageMetaData> combinedRgbaImageMetaData; 

    unsigned largestImageWidth = 0, largestImageHeight = 0;
    findLargestImageFromDecodedImages(largestImageWidth, largestImageHeight);
    auto imageCount = 0;
    for(const auto& img : decodedRgbaImages)
    {
        unsigned pX = 0; // x coordinate is always 0, since we put images in a column in combined Image reel texture atlas
        auto pY = largestImageHeight * imageCount;
        combinedRgbaImageMetaData.emplace_back(CombinedRgbaImageMetaData{img.second.getImageName(), 
            pX, pY, 
            img.second.getWidth(), 
            img.second.getHeight()});
        ++imageCount;
    }
    return combinedRgbaImageMetaData;
}

ImageReel::Impl::Impl(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder, const std::string& outPath) :
    imageSrcDir{imgSrcDir},
    imageDecoder{imgDecoder},
    imageEncoder{imgEncoder},
    outputPath{outPath}
{
}

ImageReel::ImageReel(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder, const std::string& outPath) :
    ptr{std::make_unique<Impl>(imgSrcDir, imgDecoder, imgEncoder, outPath)}
{

}

ImageReel::~ImageReel() = default;

bool ImageReel::decodePngFilesFromDir()
{
    bool result = true;
    for(const auto& path : ptr->imageSrcDir.pngFileNameAndPathsInDir())
    {
        std::vector<unsigned char> rawImageData;
        unsigned int width, height;

        if(!ptr->imageDecoder.decode(path.second, rawImageData, width, height))
        {
            std::cout << "ERROR: Could not decode the image: " << path.first << std::endl;
            result = false;
        }

        if(width > 0 && height > 0)
        {
            ptr->decodedRgbaImages.insert(std::make_pair(path.second, RgbaImage{path.first, width, height, std::move(rawImageData)}));
        }
        else
        {
            std::cout << "ERROR: Image height/width not correct, height: " << height 
                << ", width: " << width << ", path: "<< path.second << std::endl;
        }
    }
    return result;
}

bool ImageReel::encodeCombinedImage()
{
    ptr->composeCombinedImage();
    auto outputFilePath = ptr->outputPath / std::filesystem::path{"test_image.png"};
    
    std::cout << "combinedImage size: " << ptr->combinedImage.size() << std::endl;
    unsigned width = 0, height = 0;
    ptr->getImageReelSize(width, height);
    return ptr->imageEncoder.encode(outputFilePath.string(), ptr->combinedImage, width, height);
}

std::vector<CombinedRgbaImageMetaData> ImageReel::getCombinedRgbaImageMetaData()
{
    return ptr->createRgbaImageMetaDataForCombinedImage();
}

}