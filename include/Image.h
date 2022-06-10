
#include <memory>

class Image
{
    public:
        Image();
        ~Image();
    private:
        struct Impl;
        std::unique_ptr<Impl> ptr;

};