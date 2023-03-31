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
    Image EXAMPLE_part8_r;
    Image EXAMPLE_part8_g;
    Image EXAMPLE_part8_b;
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
    EXAMPLE_part8_r.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part8_r.tga");
    EXAMPLE_part8_g.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part8_g.tga");
    EXAMPLE_part8_b.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/examples/EXAMPLE_part8_b.tga");
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


    // Part 3: Screen
    cout << "Part 3: Screen" << endl;
    Image tempImage = Multiply(layer1, pattern2);
    
    tempImage.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/tempImage.tga");
    Image officialTempImage;
    officialTempImage.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/tempImage.tga");
    Image part3 = Screen(text1, officialTempImage);
    
    part3.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part3.tga");
    passedTests += compareImages(part3, EXAMPLE_part3);

    // Part 4: Multiply then Subtract
    cout << "Part 4: Multiply then Subtract" << endl;
    Image tempImage2 = Multiply(layer2, circles);
    tempImage2.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/tempImage2.tga");
    Image officialTempImage2;
    officialTempImage2.loadImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/tempImage2.tga");
    Image part4 = Subtract(officialTempImage2, pattern2);
    part4.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part4.tga");
    passedTests += compareImages(part4, EXAMPLE_part4);

    // Part 5: Overlay
    cout << "Part 5: Overlay" << endl;
    Image part5 = Overlay(pattern1, layer1);
    part5.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part5.tga");
    passedTests += compareImages(part5, EXAMPLE_part5);

    // Part 6: Add Green
    cout << "Part 6: Add Green" << endl;
    Image part6 = addGreen(car);
    part6.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part6.tga");
    passedTests += compareImages(part6, EXAMPLE_part6);

    // Part 7: Scale Red & Blue
    cout << "Part 7: Scale Red & Blue" << endl;
    Image part7 = scaleRed(car);
    part7.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part7.tga");
    passedTests += compareImages(part7, EXAMPLE_part7);

    // Part 8: Split into three channels
    int part8PassedTests = 0;
    cout << "Part 8: Split Into Channels" << endl;
    Image part8 = splitChannels("red", car);
    part8.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part8_r.tga");
    part8PassedTests += compareImages(part8, EXAMPLE_part8_r);
    
    Image part8_g = splitChannels("green", car);
    part8_g.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part8_g.tga");
    part8PassedTests += compareImages(part8_g, EXAMPLE_part8_g);
    
    Image part8_b = splitChannels("blue", car);
    part8_b.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part8_b.tga");
    part8PassedTests += compareImages(part8_b, EXAMPLE_part8_b);

    if (part8PassedTests == 3) {
        passedTests++;
    }

    // Part 9: Combine three channels
    cout << "Part 9: Combine Channels" << endl;
    Image part9 = combineChannels(layer_red, layer_green, layer_blue);
    part9.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part9.tga");
    passedTests += compareImages(part9, EXAMPLE_part9);

    // Part 10: Rotate
    cout << "Part 10: Rotate" << endl;
    Image part10 = Rotate(text2);
    part10 = Rotate(part10);
    part10.writeToImage("C:/Users/dylan/Desktop/temporary downloads/project 2 temp/output/part10.tga");
    passedTests += compareImages(part10, EXAMPLE_part10);


    // TESTS END
    cout << "Passed " << passedTests << " out of 10 tests." << endl;

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
