#pragma once

#include <memory>
#include <string>
#include <map>

namespace BasicTextureAtlas
{

class ImageSrcDir
{
    public:
        ImageSrcDir(); 
        ImageSrcDir(const std::string& directoryPath);
        ~ImageSrcDir();
        std::map<std::string, std::string> pngFileNameAndPathsInDir();
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr; 
};

}