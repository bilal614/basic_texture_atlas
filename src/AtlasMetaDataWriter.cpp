#include "AtlasMetaDataWriter.h"

#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>

namespace BasicTextureAtlas
{

struct AtlasMetaDataWriter::Impl
{
    Impl(const std::string& directoryPath, 
        const std::string& atlasFileName,
        const std::vector<CombinedRgbaImageMetaData>& comboImgMetaData);

    std::string composeMataDataFileEntry(const CombinedRgbaImageMetaData& metaData);
    bool writeMetaDataEntries();
    std::vector<CombinedRgbaImageMetaData> combinedImageMetaData;
    std::filesystem::path atlasFilePath;
};

AtlasMetaDataWriter::Impl::Impl(const std::string& directoryPath, 
    const std::string& atlasFileName,
    const std::vector<CombinedRgbaImageMetaData>& comboImgMetaData) : 
        atlasFilePath{std::filesystem::path{directoryPath} / std::filesystem::path{atlasFileName}},
        combinedImageMetaData{comboImgMetaData}
{
}

std::string AtlasMetaDataWriter::Impl::composeMataDataFileEntry(const CombinedRgbaImageMetaData& metaData)
{
    std::stringstream sStrm;
    sStrm << "[Image]" << std::endl;
    sStrm << "name: " << metaData.imageName << std::endl;
    sStrm << "x: " << metaData.xAxisCoordinate << std::endl;
    sStrm << "y: " << metaData.yAxisCoordinate << std::endl;
    sStrm << "width: " << metaData.width << std::endl;
    sStrm << "height: " << metaData.height << std::endl;
    sStrm << std::endl;
    return sStrm.str(); 
}

bool AtlasMetaDataWriter::Impl::writeMetaDataEntries()
{
    bool result = true;
    std::fstream atlasFileHandle;
    atlasFileHandle.open(atlasFilePath.string(), std::ios::out);
    if (!atlasFileHandle) 
    {
        std::cout << "ERROR: File not created!" << std::endl;
        result = false;
    }
    else 
    {
        for(const auto& data : combinedImageMetaData)
        {
            auto entry = composeMataDataFileEntry(data);
            if(!entry.empty())
            {
                atlasFileHandle << entry;
            }
            else
            {
                result = false;
            }
        }
        atlasFileHandle.close();
    }
    return result;
}

AtlasMetaDataWriter::AtlasMetaDataWriter(const std::string& directoryPath, 
    const std::string& atlasFileName, 
    const std::vector<CombinedRgbaImageMetaData>& comboImgMetaData) :
    ptr{std::make_unique<Impl>(directoryPath, atlasFileName, comboImgMetaData)}
{

}

AtlasMetaDataWriter::~AtlasMetaDataWriter() = default;

bool AtlasMetaDataWriter::writeMetaDataFile()
{
    auto result = ptr->writeMetaDataEntries();
    if(result)
    {
        std::cout << "INFO: Metadata file written to location: " << ptr->atlasFilePath.string() << std::endl;
    }
    else
    {
        std::cout << "ERROR: Error occurred in writing metadata file." << std::endl;
    }
    return result;
}

}