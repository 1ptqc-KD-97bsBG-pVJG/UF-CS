#include "Image.h"
#include "ImageFunctions.h"
#include <filesystem>
#include <iostream>
#include <string>

void printHelp() {
    cout << "Project 2: Image Processing, Spring 2023" << endl;
    cout << endl;
    cout << "Usage:" << endl;
    cout << "\t./project2.out [output] [firstImage] [method] [...]" << endl;
}

int main(int argc, char* argv[]) {
    if (argc == 1 || (argc == 2 && std::string(argv[1]) == "--help")) {
        printHelp();
        return 0;
    }

    std::string outputFile = argv[1];
    std::string firstImageFile = argv[2];

    Image trackingImage;

    if (firstImageFile.find(".tga") == std::string::npos) {
        std::cerr << "Invalid file name." << std::endl;
        return 1;
    }

    try {
        trackingImage.loadImage("./" + firstImageFile);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "File does not exist." << std::endl;
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
                secondImage.loadImage("./" + secondImageFile);
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
            if (greenLayerFile.find(".tga") == std::string::npos) {
                std::cerr << "Invalid argument, invalid file name." << std::endl;
                return 1;
            }

            try {
                greenLayer.loadImage("./" + greenLayerFile);
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
            if (blueLayerFile.find(".tga") == std::string::npos) {
                std::cerr << "Invalid argument, invalid file name." << std::endl;
                return 1;
            }

            try {
                blueLayer.loadImage("./" + blueLayerFile);
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
            if (method == "onlyred") {
                trackingImage = splitChannels("red", trackingImage);
            }
            else if (method == "onlygreen") {
                trackingImage = splitChannels("green", trackingImage);
            }
            else if (method == "onlyblue") {
                trackingImage = splitChannels("blue", trackingImage);
            }
        }
        else if (method == "addred" || method == "addgreen" || method == "addblue") {
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }

            try {
                std::stoi(argv[i]);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument, expected number." << std::endl;
                return 1;
            }

            if (method == "addred") {
                trackingImage = addRed(trackingImage, std::stoi(argv[i]));
            }
            else if (method == "addgreen") {
                trackingImage = addGreen(trackingImage, std::stoi(argv[i]));
            }
            else if (method == "addblue") {
                trackingImage = addBlue(trackingImage, std::stoi(argv[i]));
            }
        }

        else if (method == "scalered" || method == "scalegreen" || method == "scaleblue") {
            i++;
            if (i >= argc) {
                std::cerr << "Missing argument." << std::endl;
                return 1;
            }

            try {
                std::stoi(argv[i]);
            }
            catch (const std::invalid_argument& e) {
                std::cerr << "Invalid argument, expected number." << std::endl;
                return 1;
            }
            
            if (method == "scalered") {
                trackingImage = scaleRed(trackingImage, std::stoi(argv[i]));
            }
            else if (method == "scalegreen") {
                trackingImage = scaleGreen(trackingImage, std::stoi(argv[i]));
            }
            else if (method == "scaleblue") {
                trackingImage = scaleBlue(trackingImage, std::stoi(argv[i]));
            }
        }
        else {
            std::cerr << "Invalid method name." << std::endl;
            return 1;
        }
    }

    try {
        trackingImage.writeToImage("./" + outputFile);
    }
    catch (const std::runtime_error& e) {
        std::cerr << "Failed to save output file." << std::endl;
        return 1;
    }

    return 0;
}
