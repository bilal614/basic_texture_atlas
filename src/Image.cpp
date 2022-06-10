#include "Image.h"

struct Image::Impl
{

};

Image::Image() : 
    ptr{std::make_unique<Impl>()}
{

}

Image::~Image() = default;