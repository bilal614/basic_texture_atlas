#include "ImageEncoder.h"

#include "lodepng.h"
#include <cmath>
#include <iostream>

namespace BasicTextureAtlas
{

bool ImageEncoder::encode(const std::string& filePath, const std::vector<unsigned char>& image, const unsigned width, const unsigned height)
{
    lodepng::State state;
    state.info_raw.colortype = LCT_RGBA;
    state.info_raw.bitdepth = 8;
    // output color type
    state.info_png.color.colortype = LCT_RGBA;
    state.info_png.color.bitdepth = 8;
    state.encoder.auto_convert = 0;
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