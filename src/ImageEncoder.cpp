#include "ImageEncoder.h"

#include "lodepng.h"
#include <cmath>
#include <iostream>

namespace BasicTextureAtlas
{

struct ImageEncoder::Impl
{

};

ImageEncoder::ImageEncoder() :
    ptr{std::make_unique<ImageEncoder::Impl>()}
{
}

ImageEncoder::~ImageEncoder() = default;

bool ImageEncoder::encode(const std::string& filePath, const std::vector<unsigned char>& image, const unsigned width, const unsigned height)
{
    std::vector<unsigned char> png;

    auto error = lodepng::encode(png, image, width, height);
    if(!error)
    {
        lodepng::save_file(png, filePath);
    }
    else
    {
        std::cout << "Could not save file" << std::endl;
        return false;
    }

    if(error) 
    {
        std::cout << "encoder error " << error << ": "<< lodepng_error_text(error) << std::endl;
        return false;
    }
    return true;
}

}