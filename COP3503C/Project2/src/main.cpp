#include "Image.h"
#include "ImageFunctions.h"
#include <filesystem>
#include <iostream>
#include <string>

void printHelp() {
    std::cout << "Project 2: Image Processing, Spring 2023" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  ./project2.out [output] [firstImage] [method] [...]" << std::endl;
}

int main(int argc, char* argv[]) {
    cout << "argc: " << argc << endl;

    // temporary for debugging
    if (argc > 1) {
        cout << "argv[1]: " << argv[1] << endl;
    }


    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")) {
        printHelp();
        return 0;
    }

    std::string outputFile = argv[1];
    std::string firstImageFile = argv[2];

    Image trackingImage; // Your custom image class


    //  If the method expects a filename argument, and the argument does not end in .tga, print "Invalid argument, invalid file name." If the file does not exist, print "Invalid argument, file does not exist."
    if (firstImageFile.find(".tga") == std::string::npos) {
        std::cerr << "Invalid argument, invalid file name." << std::endl;
        return 1;
    }

    try {
        trackingImage.loadImage("./" + firstImageFile);
    }
    catch (int error) {
        std::cerr << "Invalid argument, file does not exist." << std::endl;
        return 1;
    }

    // Iterate through the remaining arguments
    for (int i = 3; i < argc; ++i) {
        std::string method = argv[i];

        if (method == "multiply") {
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            std::string secondImageFile = argv[i];
            Image secondImage;
            try {
                secondImage.loadImage("./" + secondImageFile);
            }
            catch (int error) {
                std::cerr << "Invalid file name." << std::endl;
                return 1;
            }
            // Implement the multiply method
            Multiply(trackingImage, secondImage);
        }
        else if (method == "subtract") {
            // Implement the subtract method
        }
        else if (method == "overlay") {
            // Implement the overlay method
        }
        else if (method == "screen") {
            // Implement the screen method
        }
        else if (method == "combine") {
            // Implement the combine method
        }
        else if (method == "flip") {
            // Implement the flip method
        }
        else {
            std::cerr << "Invalid method name." << std::endl;
            return 1;
        }
    }

    try {
        trackingImage.writeToImage(outputFile);
    }
    catch (int error) {
        std::cerr << "Failed to save output file." << std::endl;
        return 1;
    }

    return 0;
}



// CLI explanation:
// You will need to implement several methods in your CLI that the user can call. The methods are discussed below.
// • multiply: This method takes one additional argument, the second image to use in the multipli- cation process, alongside your tracking image.
// • subtract: This method takes one additional argument, the second image to use in the subtract algorithm, alongside your tracking image. The first image, the tracking image, will be the top layer. The additional image argument constitutes the bottom layer.
// • overlay: This method takes one additional argument, the second image to use in the overlay algorithm, alongside your tracking image. The first image, the tracking image, will be the top layer. The additional image argument constitutes the bottom layer.
// • screen: This method takes one additional argument, the second image to use in the screen algorithm, alongside your tracking image. The first image, the tracking image, will be the bottom layer. The additional image argument constitutes the top layer.
// • combine: This method is similar to what you did in task 9 of Part 2, where three individual files each provide one channel of the resulting image. This method takes two additional arguments, the source for the green layer (the first additional argument), and the source for the blue layer (the second additional argument). The source for the red layer is the tracking image.
// • flip: This method takes no additional argument, and simply flips the tracking image.
// • onlyred: This method takes no additional arguments, and simply retrieves the red channel from
// the image, similar to how you did in task 8.
// • onlygreen: This method takes no additional arguments, and simply retrieves the green channel from the image, similar to how you did in task 8.
// • onlyblue: This method takes no additional arguments, and simply retrieves the blue channel from the image, similar to how you did in task 8.
// • addred: This method adds a certain value to the red channel of an image. This method takes one additional argument, the amount to add to the red channel. This will need to be converted to an integer.
// • addgreen: This method adds a certain value to the green channel of an image. This method takes one additional argument, the amount to add to the red channel. This will need to be converted to an integer.
// • addblue: This method adds a certain value to the blue channel of an image. This method takes one additional argument, the amount to add to the red channel. This will need to be converted to an integer.
// • scalered: This method scales the red channel of an image. This method takes one additional argument, the amount to scale the red channel. This will need to be converted to an integer.
// • scalegreen: This method scales the green channel of an image. This method takes one additional argument, the amount to scale the red channel. This will need to be converted to an integer.
// • scaleblue: This method scales the blue channel of an image. This method takes one additional argument, the amount to scale the red channel. This will need to be converted to an integer.

// example CLI usage:
// bash-5.2$ ./project2.out --help
// Project 2: Image Processing, Spring 2023
// Usage:
//     ./project2.out [output] [firstImage] [method] [...]
// bash-5.2$ ./project2.out
// Project 2: Image Processing, Spring 2023
// Usage:
//     ./project2.out [output] [firstImage] [method] [...]
// bash-5.2$ ./project2.out out.tga car.tga multiply part1.tga
// Multiplying car.tga and part1.tga ...
// ... and saving output to out.tga!
// bash-5.2$ ./project2.out out.tga car.tga multiply part1.tga screen part2.tga
// Multiplying car.tga and part1.tga ...
// ... and subtracting part2.tga from previous step ...
// ... and saving output to out.tga!
// bash-5.2$ ./project2.out out.tga car.tga flip flip flip flip
// Flipping car.tga ...
// ... and flipping output of previous step ...
// ... and flipping output of previous step ...
// ... and flipping output of previous step ...
// ... and saving output to out.tga!
// bash-5.2$ ./project2.out out.tga car.tga scalegreen 5 addred 100 scaleblue 0
// Scaling the green channel of car.tga by 5 ...
// ... and adding +100 to red channel of previous step ...
// ... and scaling the blue channel of previous step by 0 ...
// ... and saving output to out.tga!
// bash-5.2$ ./project2.out out.tga red.tga combine blue.tga green.tga
// Combining channels of red.tga, blue.tga, and green.tga ...
// ... and saving output to out.tga!
// bash-5.2$ ./project2.out out.tga
// Invalid file name.
// bash-5.2$ ./project2.out out.tga part2.tga weirdmethod