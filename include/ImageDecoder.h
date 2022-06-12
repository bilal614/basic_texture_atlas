#pragma once

#include <string>
#include <vector>

namespace BasicTextureAtlas
{

class ImageDecoder
{
    public:
        bool decode(const std::string& filePath, 
            std::vector<unsigned char>& image, 
            unsigned int& width,
            unsigned int& height);
};
}