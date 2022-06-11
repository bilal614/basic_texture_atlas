#pragma once

#include <memory>

namespace BasicTextureAtlas
{
class ImageEncoder;
class ImageDecoder;
class ImageSrcDir;

class ImageReel
{
    public:
        ImageReel(ImageSrcDir& imgSrcDir, ImageDecoder& imgDecoder, ImageEncoder& imgEncoder);
        ~ImageReel();
        bool decodePngFilesFromDir();
        bool encodeCombinedImage();

    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
    
};
}