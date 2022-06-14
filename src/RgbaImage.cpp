#include "RgbaImage.h"

namespace BasicTextureAtlas
{

constexpr unsigned long NrOfRgbaChannels = 4;

struct RgbaImage::Impl
{
    Impl(std::string imgName, unsigned width, unsigned height, std::vector<unsigned char>&& imageData);
    std::string imageName;
    unsigned int width, height;
    std::vector<unsigned char> rawImageData;

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
};

RgbaImage::Impl::Impl(std::string imgName, unsigned w, unsigned h, std::vector<unsigned char>&& imageData) :
    imageName{imgName}, width{w}, height{h}, rawImageData{std::move(imageData)}
{
}

std::vector<RgbaImage::Impl::PixelRgba> RgbaImage::Impl::rawImageDataToPixelRgba(const std::vector<unsigned char>& srcImg)
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

std::vector<unsigned char> RgbaImage::Impl::pixelRgbaDataToRawImage(const std::vector<PixelRgba>& src)
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


RgbaImage::RgbaImage(std::string imgName, unsigned w, unsigned h, std::vector<unsigned char>&& imageData) :
    ptr{std::make_unique<Impl>(imgName, w, h, std::move(imageData))}
{

}

RgbaImage::~RgbaImage() = default;

RgbaImage::RgbaImage(RgbaImage&& rhs) noexcept = default;

RgbaImage& RgbaImage::operator=(RgbaImage&& rhs) noexcept = default;


std::string RgbaImage::getImageName() const
{
    return ptr->imageName;
}

unsigned RgbaImage::getImageSize() const
{
    return ptr->width*ptr->height;
}

unsigned RgbaImage::getWidth() const
{
    return ptr->width;
}

unsigned RgbaImage::getHeight() const
{
    return ptr->height;
}

std::vector<unsigned char> RgbaImage::addPadding(unsigned desiredWidth, unsigned desiredHeight) const
{
    if(ptr->height*ptr->width*NrOfRgbaChannels != ptr->rawImageData.size())
    {
        return std::vector<unsigned char>();
    }
    Impl::PixelRgba whitePixel = {255, 255, 255, 255};
    auto src = ptr->rawImageDataToPixelRgba(ptr->rawImageData);
    std::vector<Impl::PixelRgba> target{desiredWidth * desiredHeight, whitePixel};
    for(unsigned int i = 0; i < ptr->height; i++)
    {
        for(unsigned int j = 0; j < ptr->width; j++)
        {
            auto srcIdx = i*ptr->width + j;
            if(srcIdx >= src.size())
            {
                break;
            }

            auto targetIdx = i*desiredWidth + j;
            if(targetIdx >= target.size())
            {
                break;
            }
            target[targetIdx] = src[srcIdx];
        }
    }
    return ptr->pixelRgbaDataToRawImage(target);
}

}