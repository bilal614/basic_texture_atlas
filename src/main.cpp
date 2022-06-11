#include "ImageDecoder.h"
#include "ImageEncoder.h"
#include "ImageReel.h"
#include "ImageSrcDir.h"
#include <iostream>

int main(int argc, char *argv[]) 
{
    std::string directoryPath = argc > 1 ? argv[1] : "test_images";

    BasicTextureAtlas::ImageSrcDir imgSrcDir{directoryPath};
    BasicTextureAtlas::ImageDecoder decoder;
    BasicTextureAtlas::ImageEncoder encoder;
    BasicTextureAtlas::ImageReel imageReel{imgSrcDir, decoder, encoder};

    auto result = imageReel.decodePngFilesFromDir();
    result &= imageReel.encodeCombinedImage();

    return result;

}