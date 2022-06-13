#include "ImageSrcDir.h"

#include <algorithm>
#include <filesystem>
#include <iostream>

namespace 
{
    const std::string PngExtension = ".png";
}

namespace BasicTextureAtlas
{ 

struct ImageSrcDir::Impl
{
    Impl(const std::string& dirPath);
    std::filesystem::path directoryPath;
    std::vector<std::filesystem::path> pngFilesInDirectory;
};

ImageSrcDir::Impl::Impl(const std::string& dirPath) :
    directoryPath{dirPath}
{
    if(std::filesystem::exists(directoryPath))
    {
        for(const auto& dirEntry : std::filesystem::recursive_directory_iterator(directoryPath))
        {
             if(dirEntry.path().extension().string() == PngExtension)
             {
                 pngFilesInDirectory.emplace_back(dirEntry.path());
             }
        }
    }
    else
    {
        std::cout << "WARNING: Provided directory path does not exists: " << dirPath << std::endl;
    }
}

ImageSrcDir::ImageSrcDir(const std::string& directoryPath) :
    ptr{std::make_unique<Impl>(directoryPath)}
{
}

ImageSrcDir::ImageSrcDir() : 
    ImageSrcDir(std::filesystem::current_path().string())
{
}

ImageSrcDir::~ImageSrcDir() = default;

std::map<std::string, std::string> ImageSrcDir::pngFileNameAndPathsInDir()
{
    std::map<std::string, std::string> pngFilePaths;
    std::transform(ptr->pngFilesInDirectory.begin(), 
        ptr->pngFilesInDirectory.end(), 
        std::inserter(pngFilePaths, pngFilePaths.end()), 
        [](const std::filesystem::path& path) -> auto
        {
            return std::make_pair(path.stem().string(), path.string());
        });

    return pngFilePaths;
}

}