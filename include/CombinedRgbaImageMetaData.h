#pragma once

#include <string>

namespace BasicTextureAtlas
{

struct CombinedRgbaImageMetaData
{
    CombinedRgbaImageMetaData(const std::string& imgName, 
        unsigned x, 
        unsigned y,
        unsigned w,
        unsigned h) : 
            imageName{imgName}, 
            xAxisCoordinate{x},
            yAxisCoordinate{y},
            width{w},
            height{h}
        {
        }

    std::string imageName;
    unsigned xAxisCoordinate, yAxisCoordinate;
    unsigned width, height;
};

}