#include <memory>
#include <vector>


class ImageEncoder
{
    public:
        ImageEncoder();
        ~ImageEncoder();
        bool encode(const char* filename, const std::vector<unsigned char>& image, unsigned width, unsigned height);
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;
};