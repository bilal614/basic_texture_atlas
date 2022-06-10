#include <memory>
#include <vector>


class ImageDecoder
{
    public:
        ImageDecoder();
        ~ImageDecoder();
        bool decode(const char* filename, std::vector<unsigned char>& image, unsigned int desiredWidth, unsigned int desiredHeight);
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
};