#pragma once

#include <memory>
#include <vector>

#include "CombinedRgbaImageMetaData.h"

namespace BasicTextureAtlas
{

class AtlasMetaDataWriter
{
    public:
        AtlasMetaDataWriter(const std::string& directoryPath, 
            const std::string& atlasFileName, 
            const std::vector<CombinedRgbaImageMetaData>& combinedImageMetaData);
        ~AtlasMetaDataWriter();
        bool writeMetaDataFile();
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
};

}