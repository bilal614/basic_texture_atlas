#pragma once

#include <string>
#include <vector>

namespace BasicTextureAtlas
{
class ImageEncoder
{
    public:
        bool encode(const std::string& filePath, const std::vector<unsigned char>& image, unsigned width, unsigned height);
};

}