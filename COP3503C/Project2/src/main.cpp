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

// bool isNumber(const std::string& s) {
//     return !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
// }

int main(int argc, char* argv[]) {
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")) {
        printHelp();
        return 0;
    }

    cout << "argc: " << argc << endl;
    if (argc > 1) {
        for (int i = 0; i < argc; i++) {
            cout << "argv[" << i << "]: " << argv[i] << endl;
        }
    }

    std::string outputFile = argv[1];
    std::string firstImageFile = argv[2];

    Image trackingImage;

    if (firstImageFile.find(".tga") == std::string::npos) {
        std::cerr << "Invalid argument, invalid file name." << std::endl;
        return 1;
    }

    try {
        trackingImage.loadImage("./inputs/" + firstImageFile);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Invalid argument, file does not exist." << std::endl;
        return 1;
    }

    // Iterate through the remaining arguments
    for (int i = 3; i < argc; ++i) {
        std::string method = argv[i];

        if (method == "multiply" || method == "subtract" || method == "overlay" || method == "screen") {
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            std::string secondImageFile = argv[i];
            if (secondImageFile.find(".tga") == std::string::npos) {
                std::cerr << "Invalid argument, invalid file name." << std::endl;
                return 1;
            }
            Image secondImage;
            try {
                secondImage.loadImage("./inputs/" + secondImageFile);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "Invalid argument, file does not exist." << std::endl;
                return 1;
            }

            // LOOKS GOOD

            if (method == "multiply") {
                trackingImage = Multiply(trackingImage, secondImage);
            }
            else if (method == "subtract") {
                trackingImage = Subtract(trackingImage, secondImage);
            }
            else if (method == "overlay") {
                trackingImage = Overlay(trackingImage, secondImage);
            }
            else if (method == "screen") {
                trackingImage = Screen(trackingImage, secondImage);
            }
        }
        // LOOKS GOOD
        else if (method == "combine") {
            // Implement the combine method
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            std::string greenLayerFile = argv[i];
            Image greenLayer;
            try {
                greenLayer.loadImage("./inputs/" + greenLayerFile);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "Invalid argument, file does not exist." << std::endl;
                return 1;
            }
            
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            
            std::string blueLayerFile = argv[i];
            Image blueLayer;
            try {
                blueLayer.loadImage("./inputs/" + blueLayerFile);
            }
            catch (const std::runtime_error& e) {
                std::cerr << "Invalid argument, file does not exist." << std::endl;
                return 1;
            }

            trackingImage = combineChannels(trackingImage, greenLayer, blueLayer);
        }
        // LOOKS GOOD
        else if (method == "flip") {
            trackingImage = Rotate(trackingImage);
            trackingImage = Rotate(trackingImage);
        }
        else if (method == "onlyred" || method == "onlygreen" || method == "onlyblue") {
            // scale functions
        }
        else if (method == "addred" || method == "addgreen" || method == "addblue" || method == "scalered" || method == "scalegreen" || method == "scaleblue") {
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }
            // std::string valueStr = argv[i];
            // if (!isNumber(valueStr)) {
            //     std::cerr << "Invalid argument, expected number." << std::endl;
            //     return 1;
            // }
            // add and scale functions
        }
        else {
            std::cerr << "Invalid method name." << std::endl;
            return 1;
        }
    }

    try {
        trackingImage.writeToImage("./output/" + outputFile);
        // temporary
        cout << "Successfully output to " << outputFile << endl;
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Failed to save output file." << std::endl;
        return 1;
    }

    return 0;
}
