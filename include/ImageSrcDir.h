#pragma once

#include <memory>
#include <string>
#include <vector>

namespace BasicTextureAtlas
{

class ImageSrcDir
{
    public:
        ImageSrcDir(); 
        ImageSrcDir(const std::string& directoryPath);
        ~ImageSrcDir();
        std::vector<std::string> pngFilePathsInDir();
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr; 
};

}