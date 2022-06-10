
#include "ImageDecoder.h"

#include "lodepng.h"
#include <cmath>
#include <iostream>

constexpr unsigned long NrOfRgbaChannels = 4;

struct ImageDecoder::Impl
{
    struct PixelRgba
    {
        PixelRgba() : 
            red{255}, green{255}, blue{255}, alpha{255}
        {

        }
        PixelRgba(unsigned char r, unsigned char g, unsigned char b, unsigned char a) :
            red{r}, green{g}, blue{b}, alpha{a} 
        {
            
        }
        unsigned char red, green, blue, alpha;
    };

    std::vector<PixelRgba> rawImageDataToPixelRgba(const std::vector<unsigned char>& srcImg);
    std::vector<unsigned char> pixelRgbaDataToRawImage(const std::vector<PixelRgba>& src);

    std::vector<unsigned char> addPadding(const std::vector<unsigned char>& srcImg, 
        unsigned width, unsigned height, 
        unsigned desiredWidth, unsigned desiredHeight);

};

std::vector<ImageDecoder::Impl::PixelRgba> ImageDecoder::Impl::rawImageDataToPixelRgba(const std::vector<unsigned char>& srcImg)
{
    std::vector<PixelRgba> target;
    unsigned char r = 0 , g = 0, b = 0, a = 0;
    unsigned long count = 0;
    for(const auto i : srcImg)
    {
        if(count % NrOfRgbaChannels == 0)
        {
            r = i;
        }
        if(count % NrOfRgbaChannels == 1)
        {
            g = i;
        }
        if(count % NrOfRgbaChannels == 2)
        {
            b = i;
        }
        if(count % NrOfRgbaChannels == 3)
        {
            a = i;
            target.push_back(PixelRgba{r, g, b, a});
        }
        ++count;
    }
    return target;
}

std::vector<unsigned char> ImageDecoder::Impl::pixelRgbaDataToRawImage(const std::vector<PixelRgba>& src)
{
    std::vector<unsigned char> target{};
    for(auto i = 0 ; i < src.size(); i++)
    {
        target.push_back(src[i].red);
        target.push_back(src[i].green);
        target.push_back(src[i].blue);
        target.push_back(src[i].alpha);
    }
    return target;
}

std::vector<unsigned char> ImageDecoder::Impl::addPadding(const std::vector<unsigned char>& srcImg, 
    unsigned width, unsigned height, 
    unsigned desiredWidth, unsigned desiredHeight)
{
    if(height*width*NrOfRgbaChannels != srcImg.size())
    {
        return std::vector<unsigned char>();
    }
    PixelRgba whitePixel = {255, 255, 255, 255};
    auto src = rawImageDataToPixelRgba(srcImg);
    std::vector<PixelRgba> target{desiredWidth * desiredHeight, whitePixel};
    for(unsigned int i = 0; i < height; i++)
    {
        for(unsigned int j = 0; j < width; j++)
        {
            auto idx = i*width + j;
            if(idx >= target.size() || idx >= src.size())
            {
                break;
            }
            target[idx] = src[idx];
        }
    }
    return pixelRgbaDataToRawImage(target);
}

ImageDecoder::ImageDecoder() :
    ptr{std::make_unique<Impl>()}
{
}

ImageDecoder::~ImageDecoder() = default;

bool ImageDecoder::decode(const char* filename, std::vector<unsigned char>& image, const unsigned int desiredWidth, const unsigned int desiredHeight)
{
    std::vector<unsigned char> png;
    unsigned width, height;

    auto error = lodepng::load_file(png, filename);
    if(!error)
    {
        std::vector<unsigned char> temp;
        error = lodepng::decode(temp, width, height, png);
        image = ptr->addPadding(temp, width, height, desiredWidth, desiredHeight);
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

