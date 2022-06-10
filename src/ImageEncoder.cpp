#include "ImageEncoder.h"

#include "lodepng.h"
#include <cmath>
#include <iostream>

struct ImageEncoder::Impl
{

};

ImageEncoder::ImageEncoder() :
    ptr{std::make_unique<ImageEncoder::Impl>()}
{
}

ImageEncoder::~ImageEncoder() = default;

bool ImageEncoder::encode(const char* filename, const std::vector<unsigned char>& image, const unsigned width, const unsigned height)
{
    std::vector<unsigned char> png;
    lodepng::State state; //optionally customize this one
    //state.encoder.text_compression = LodePNGColorType::LCT_RGBA; 

    state.info_png.color.colortype = LCT_RGBA;
    state.info_png.color.bitdepth = 8;
    state.encoder.auto_convert = 0;
    auto error = lodepng::encode(png, image, width, height, state);
    if(!error)
    {
        lodepng::save_file(png, filename);
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
