#include "Image.h"
#include "ImageFunctions.h"
#include <filesystem>
#include <iostream>
#include <string>

int compareImages(Image &firstImage, Image &secondImage) {
    if (firstImage == secondImage) {
        cout << "Images are the same!" << endl;
        return 1;
    } else {
        cout << "Images are different. Test has failed!" << endl;
        return 0;
    }
}

int main()
{
    int passedTests = 0;
    double totalTests = 12;
    
    // define images
    Image layer1;
    Image layer2;
    Image pattern1;
    Image pattern2;
    Image text1;
    Image text2;
    Image car;
    Image circles;
    Image layer_red;
    Image layer_green;
    Image layer_blue;

    // load images
    layer1.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/layer1.tga");
    layer2.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/layer2.tga");
    pattern1.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/pattern1.tga");
    pattern2.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/pattern2.tga");
    text1.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/text.tga");
    text2.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/text2.tga");
    car.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/car.tga");
    circles.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/circles.tga");
    layer_red.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/layer_red.tga");
    layer_green.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/layer_green.tga");
    layer_blue.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/input/layer_blue.tga");

    // define example images
    Image EXAMPLE_part1;
    Image EXAMPLE_part2;
    Image EXAMPLE_part3;
    Image EXAMPLE_part4;
    Image EXAMPLE_part5;
    Image EXAMPLE_part6;
    Image EXAMPLE_part7;
    Image EXAMPLE_part8;
    Image EXAMPLE_part9;
    Image EXAMPLE_part10;

    // load example images
    EXAMPLE_part1.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part1.tga");
    EXAMPLE_part2.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part2.tga");
    EXAMPLE_part3.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part3.tga");
    EXAMPLE_part4.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part4.tga");
    EXAMPLE_part5.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part5.tga");
    EXAMPLE_part6.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part6.tga");
    EXAMPLE_part7.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part7.tga");
    EXAMPLE_part8.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part8.tga");
    EXAMPLE_part9.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part9.tga");
    EXAMPLE_part10.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part10.tga");

    // TESTS START

    // Part 1: Multiply
    cout << "Part 1: Multiply" << endl;
    Image part1 = Multiply(layer1, pattern1);
    part1.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part1.tga");
    passedTests += compareImages(part1, EXAMPLE_part1);

    // Part 2: Subtract
    cout << "Part 2: Subtract" << endl;
    Image part2 = Subtract(car, layer2);
    part2.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part2.tga");
    passedTests += compareImages(part2, EXAMPLE_part2);

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
