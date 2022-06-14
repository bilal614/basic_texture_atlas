#pragma once

#include <memory>
#include <string>
#include <vector>

namespace BasicTextureAtlas
{

class RgbaImage
{
public:
    RgbaImage(std::string imgName, unsigned width, unsigned height, std::vector<unsigned char>&& imageData);
    ~RgbaImage();
    RgbaImage(RgbaImage&& rhs) noexcept;
    RgbaImage& operator=(RgbaImage&& rhs) noexcept;
    RgbaImage(RgbaImage& rhs) = delete;
    RgbaImage& operator=(const RgbaImage& t) = delete;

    std::string getImageName() const;
    unsigned getImageSize() const;
    unsigned getWidth() const;
    unsigned getHeight() const;
    std::vector<unsigned char> addPadding( unsigned desiredWidth, unsigned desiredHeight) const;

private:
    struct Impl;
    std::unique_ptr<Impl> ptr;

};

}