#pragma once

#include <memory>
#include <string>
#include <vector>

namespace BasicTextureAtlas
{

class ImageDecoder
{
    public:
        ImageDecoder();
        ~ImageDecoder();
        bool decode(const std::string& filePath, 
            std::vector<unsigned char>& image, 
            unsigned int& width,
            unsigned int& height,
            unsigned int desiredWidth, 
            unsigned int desiredHeight);
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
};
}