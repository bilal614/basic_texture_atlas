
#include "ImageDecoder.h"

#include "lodepng.h"
#include <cmath>
#include <iostream>


namespace BasicTextureAtlas
{

bool ImageDecoder::decode(const std::string& filePath, 
    std::vector<unsigned char>& image,
    unsigned int& width,
    unsigned int& height)
{
    std::vector<unsigned char> png;

    auto error = lodepng::load_file(png, filePath);
    if(!error)
    {
        lodepng::State state;
        error = lodepng::decode(image, width, height, state, png);

        if(state.info_png.color.colortype != LCT_RGBA)
        {
            std::cout << "WARNING: Image does not have RGBA color type." << std::endl;
        }
    }
    else
    {
        std::cout << "ERROR: Could not load file" << std::endl;
        return false;
    }
    if(error) 
    {
        std::cout << "decoder error " << error << ": " << lodepng_error_text(error) << std::endl;
        return false;
    }
    return true;
}

}
