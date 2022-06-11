#pragma once

#include <memory>
#include <string>
#include <vector>

namespace BasicTextureAtlas
{
class ImageEncoder
{
    public:
        ImageEncoder();
        ~ImageEncoder();
        bool encode(const std::string& filePath, const std::vector<unsigned char>& image, unsigned width, unsigned height);
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
};

}