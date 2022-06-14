#include "AtlasMetaDataWriter.h"
#include "ImageDecoder.h"
#include "ImageEncoder.h"
#include "ImageReel.h"
#include "ImageSrcDir.h"
#include <iostream>
#include <filesystem>

int main(int argc, char *argv[]) 
{
    std::string directoryPath = argc > 1 ? argv[1] : "test_images";
    auto hostAppWorkingDir =  std::filesystem::path{argv[0]}.parent_path().string();;

    BasicTextureAtlas::ImageSrcDir imgSrcDir{directoryPath};
    BasicTextureAtlas::ImageDecoder decoder;
    BasicTextureAtlas::ImageEncoder encoder;
    BasicTextureAtlas::ImageReel imageReel{imgSrcDir, decoder, encoder, hostAppWorkingDir};

    auto result = imageReel.decodePngFilesFromDir();
    result &= imageReel.encodeCombinedImage();

    BasicTextureAtlas::AtlasMetaDataWriter atlasMetaDataWriter{hostAppWorkingDir, "test_images_metadata.txt", imageReel.getCombinedRgbaImageMetaData()};
    atlasMetaDataWriter.writeMetaDataFile();

    return result;
}