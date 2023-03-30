#include "Image.h"
#include "ImageFunctions.h"
#include <iostream>
#include <string>

int main()
{
    std::string inputFilename = "C:/Users/dylan/Desktop/temporary downloads/project 2 temp/car.tga";
    std::string outputFilename = "output.tga";

    // Create an Image object and load the input file
    Image image;
    image.loadImage(inputFilename);

    // Get the header and pixel data from the Image object
    Image::Header header = image.getHeader();
    std::vector<Image::Pixel> pixels = image.getPixels();

    // Print some information about the TGA file
    std::cout << "Image width: " << header.width << std::endl;
    std::cout << "Image height: " << header.height << std::endl;
    std::cout << "Number of pixels: " << pixels.size() << std::endl;

    // Modify the pixel data (for example, invert the colors)
    // for (auto& pixel : pixels)
    // {
    //     pixel.red = 255 - pixel.red;
    //     pixel.green = 255 - pixel.green;
    //     pixel.blue = 255 - pixel.blue;
    // }
    Rotate(image).writeToImage(outputFilename);

    // Write the modified pixel data to a new TGA file
    image.writeToImage(outputFilename);

    return 0;
}
// 1. Use the Multiply blending mode to combine layer1.tga (top layer) with pattern1.tga (bottom layer).

// 2. Use the Subtract blending mode to combine layer2.tga (bottom layer) with car.tga (top layer).
// 3. Use the Multiply blending mode to combine layer1.tga with pattern2.tga, and store the results temporarily, in memory (aka, don’t write this to a file somewhere, just store the pixel values somewhere in your program). Load the image text.tga and, using that as the bottom layer, combine it with the previous results of layer1/pattern2 using the Screen blending mode.
// 4. Multiply layer2.tga with circles.tga, and store it. Load pattern2.tga and, using that as the bottom layer, combine it with the previous result using the Subtract blending mode.
// 5. Combine layer1.tga (as the top layer) with pattern1.tga using the Overlay blending mode.
// 6. Load car.tga and add 200 to the green channel.
// 7. Load car.tga and scale (multiply) the red channel by 4, and the blue channel by 0. This will increase the intensity of any red in the image, while negating any blue it may have.
// 8. Load car.tga and write each channel to a separate file: the red channel should be part8_r.tga, the green channel should be part8_g.tga, and the blue channel should be part8_b.tga. (Hint: If your red channel image appears all red, try writing [Red, Red, Red] instead of [Red, 0, 0] to the file—ditto for green and blue!)
// 9. Load layer_red.tga, layer_green.tga and layer_blue.tga, and combine the three files into one file. The data from layer_red.tga is the red channel of the new image, layer_green is green, and layer_blue is blue.
// 10. Load text2.tga, and rotate it 180 degrees, flipping it upside down. This is easier than you think! Try diagramming the data of an image (such as earlier in this document). What would the data look like if you flipped it? Now, how to write some code to accomplish that...?
