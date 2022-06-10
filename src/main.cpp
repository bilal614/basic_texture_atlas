#include "ImageDecoder.h"
#include "ImageEncoder.h"
#include <iostream>

int main(int argc, char *argv[]) {
    const char* filename = argc > 1 ? argv[1] : "test_images/flower_art.png";

    // auto file1 = "D:\\vm_shared\\basic_texture_atlas\\build\\test_images\\colors.png";
    // auto file2 = "D:\\vm_shared\\basic_texture_atlas\\build\\test_images\\autumn_tree.png";
    // auto file3 = "D:\\vm_shared\\basic_texture_atlas\\build\\test_images\\doodle.png";
    // auto file4 = "D:\\vm_shared\\basic_texture_atlas\\build\\test_images\\dove.png";
    // auto file5 = "D:\\vm_shared\\basic_texture_atlas\\build\\test_images\\bald_eagle.png";

    auto file1 = "test_images/dove.png";
    auto file2 = "test_images/colors.png";
    auto file3 = "test_images/autumn_tree.png";
    auto file4 = "test_images/doodle.png";
    auto file5 = "test_images/bald_eagle.png";

    ImageDecoder decoder;

    std::vector<unsigned char> image1, image2, image3, image4, image5;

    auto result = decoder.decode(file1, image1, 124, 126);
    std::cout << "result: " << result << std::endl;
    result = decoder.decode(file2, image2, 124, 124);
    std::cout << "result: " << result << std::endl;
    result = decoder.decode(file3, image3, 124, 124);
    std::cout << "result: " << result << std::endl;
    result = decoder.decode(file4, image4, 124, 124);
    std::cout << "result: " << result << std::endl;
    result = decoder.decode(file5, image5, 124, 124);
    std::cout << "result: " << result << std::endl;

    std::vector<unsigned char> combinedImage;//(image1.size() + image2.size(), 0);
    combinedImage.insert(combinedImage.end(), image1.begin(), image1.end());
    combinedImage.insert(combinedImage.end(), image2.begin(), image2.end());
    combinedImage.insert(combinedImage.end(), image3.begin(), image3.end());
    combinedImage.insert(combinedImage.end(), image4.begin(), image4.end());
    combinedImage.insert(combinedImage.end(), image5.begin(), image5.end());
    std::cout << "combinedImage size: " << combinedImage.size() << std::endl;
    ImageEncoder encoder;

    //auto outputFilePath = "D:\\vm_shared\\basic_texture_atlas\\build\\test_images\\test_image.png";
    auto outputFilePath = "test_images/test_image.png";
    result = encoder.encode(outputFilePath, combinedImage, 124, 620);

    std::cout << "result: " << result << std::endl;

    return result;

}