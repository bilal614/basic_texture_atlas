#pragma once

#include <memory>
#include <vector>

namespace BasicTextureAtlas
{

struct CombinedRgbaImageMetaData;
class ImageEncoder;
class ImageDecoder;
class ImageSrcDir;

class ImageReel
{
    public:
        ImageReel(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder, const std::string& outputPath);
        ~ImageReel();
        bool decodePngFilesFromDir();
        bool encodeCombinedImage();
        std::vector<CombinedRgbaImageMetaData> getCombinedRgbaImageMetaData();
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
    
};
}