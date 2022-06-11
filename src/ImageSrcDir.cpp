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

std::vector<std::string> ImageSrcDir::pngFilePathsInDir()
{
    std::vector<std::string> pngFilePaths;
    std::transform(ptr->pngFilesInDirectory.begin(), ptr->pngFilesInDirectory.end(), std::back_inserter(pngFilePaths), 
    [](const std::filesystem::path& path) -> std::string 
    {
        return path.string();
    });

    return pngFilePaths;
}

}