#pragma once

#include <memory>
#include <vector>

namespace BasicTextureAtlas
{

class ImageDecoder
{
    public:
        ImageDecoder();
        ~ImageDecoder();
        bool decode(const std::string& filePath, std::vector<unsigned char>& image, unsigned int desiredWidth, unsigned int desiredHeight);
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
};
}